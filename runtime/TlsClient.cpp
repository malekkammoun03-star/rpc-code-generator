#include "TlsClient.h"
#include <mbedtls/error.h>
#include <iostream>
#include <cstring>

TlsClient::TlsClient()
    : connected(false)
{
    mbedtls_net_init(&server_fd);
    mbedtls_ssl_init(&ssl);
    mbedtls_ssl_config_init(&conf);
    mbedtls_ctr_drbg_init(&ctr_drbg);
    mbedtls_entropy_init(&entropy);
    mbedtls_x509_crt_init(&ca_cert);
}

TlsClient::~TlsClient()
{
    disconnect();

    mbedtls_x509_crt_free(&ca_cert);
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);
    mbedtls_ssl_config_free(&conf);
    mbedtls_ssl_free(&ssl);
    mbedtls_net_free(&server_fd);
}

bool TlsClient::connect(const std::string &host, int port)
{
    if (connected)
    {
        disconnect();
    }

    mbedtls_net_free(&server_fd);
    mbedtls_net_init(&server_fd);
    const char *pers = "rpc_tls_client";

    int ret = mbedtls_ctr_drbg_seed(
        &ctr_drbg,
        mbedtls_entropy_func,
        &entropy,
        reinterpret_cast<const unsigned char *>(pers),
        std::strlen(pers));

    if (ret != 0)
    {
        std::cerr << "Failed to initialize random generator: "
                  << ret << std::endl;
        return false;
    }

    std::string portString = std::to_string(port);
    ret = mbedtls_net_connect(
        &server_fd,
        host.c_str(),
        portString.c_str(),
        MBEDTLS_NET_PROTO_TCP);

    if (ret != 0)
    {
        char errorBuffer[256];

        mbedtls_strerror(
            ret,
            errorBuffer,
            sizeof(errorBuffer));

        std::cerr << "TCP connection failed: "
                  << ret
                  << " - "
                  << errorBuffer
                  << std::endl;

        return false;
    }
    mbedtls_ssl_set_bio(
        &ssl,
        &server_fd,
        mbedtls_net_send,
        mbedtls_net_recv,
        nullptr);
    ret = mbedtls_ssl_config_defaults(
        &conf,
        MBEDTLS_SSL_IS_CLIENT,
        MBEDTLS_SSL_TRANSPORT_STREAM,
        MBEDTLS_SSL_PRESET_DEFAULT);

    if (ret != 0)
    {
        std::cerr << "SSL configuration failed: "
                  << ret << std::endl;
        return false;
    }

    mbedtls_ssl_conf_authmode(
        &conf,
        MBEDTLS_SSL_VERIFY_REQUIRED);

    mbedtls_ssl_conf_rng(
        &conf,
        mbedtls_ctr_drbg_random,
        &ctr_drbg);

    ret = mbedtls_x509_crt_parse_file(
        &ca_cert,
        "certs/ca-bundle.crt");

    if (ret < 0)
    {
        std::cerr << "Failed to load CA certificate bundle: "
                  << ret << std::endl;
        return false;
    }

    mbedtls_ssl_conf_ca_chain(
        &conf,
        &ca_cert,
        nullptr);

    ret = mbedtls_ssl_setup(&ssl, &conf);

    if (ret != 0)
    {
        std::cerr << "SSL setup failed: "
                  << ret << std::endl;
        return false;
    }

    ret = mbedtls_ssl_set_hostname(
        &ssl,
        host.c_str());

    if (ret != 0)
    {
        std::cerr << "Failed to set TLS hostname: "
                  << ret << std::endl;
        return false;
    }

    mbedtls_ssl_set_bio(
        &ssl,
        &server_fd,
        mbedtls_net_send,
        mbedtls_net_recv,
        nullptr);

    do
    {
        ret = mbedtls_ssl_handshake(&ssl);
    } while (ret == MBEDTLS_ERR_SSL_WANT_READ ||
             ret == MBEDTLS_ERR_SSL_WANT_WRITE);

    if (ret != 0)
    {
        char errorBuffer[256];

        mbedtls_strerror(
            ret,
            errorBuffer,
            sizeof(errorBuffer));

        std::cerr << "TLS handshake failed: "
                  << ret
                  << " - "
                  << errorBuffer
                  << std::endl;
        mbedtls_net_free(&server_fd);
        return false;
    }
    uint32_t verifyResult = mbedtls_ssl_get_verify_result(&ssl);

    if (verifyResult != 0)
    {
        char verifyBuffer[512];

        mbedtls_x509_crt_verify_info(
            verifyBuffer,
            sizeof(verifyBuffer),
            "  ",
            verifyResult);

        std::cerr << "Certificate verification failed:\n"
                  << verifyBuffer
                  << std::endl;
        mbedtls_ssl_session_reset(&ssl);
        mbedtls_net_free(&server_fd);
        return false;
    }
    connected = true;

    std::cout << "TLS handshake successful" << std::endl;

    return true;
}

void TlsClient::disconnect()
{
    if (connected)
    {
        mbedtls_ssl_close_notify(&ssl);
    }

    mbedtls_net_free(&server_fd);

    connected = false;
}

bool TlsClient::send(
    const unsigned char *data,
    size_t length)
{
    if (!connected)
        return false;

    size_t sent = 0;

    while (sent < length)
    {
        int ret = mbedtls_ssl_write(
            &ssl,
            data + sent,
            length - sent);

        if (ret > 0)
        {
            sent += static_cast<size_t>(ret);
            continue;
        }

        if (ret == MBEDTLS_ERR_SSL_WANT_READ ||
            ret == MBEDTLS_ERR_SSL_WANT_WRITE)
        {
            continue;
        }

        return false;
    }

    return true;
}

int TlsClient::receive(
    unsigned char *buffer,
    size_t length)
{
    if (!connected)
        return -1;

    return mbedtls_ssl_read(
        &ssl,
        buffer,
        length);
}