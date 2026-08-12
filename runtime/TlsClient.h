#pragma once

#include <string>

#include <mbedtls/net_sockets.h>
#include <mbedtls/ssl.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>
#include <mbedtls/x509_crt.h>

class TlsClient
{
public:
    TlsClient();
    ~TlsClient();

    bool connect(const std::string &host, int port);
    void disconnect();

    bool send(const unsigned char *data, size_t length);
    int receive(unsigned char *buffer, size_t length);

private:
    mbedtls_net_context server_fd;
    mbedtls_ssl_context ssl;
    mbedtls_ssl_config conf;
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_entropy_context entropy;
    mbedtls_x509_crt ca_cert;

    bool connected;
};