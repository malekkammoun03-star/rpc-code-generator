#include "RpcClient.h"

#include <cstdint>
#include <iostream>

RpcClient::RpcClient()
{
}

RpcClient::~RpcClient()
{
    disconnect();
}

bool RpcClient::connect(
    const std::string &host,
    int port)
{
    return tlsClient.connect(host, port);
}

void RpcClient::disconnect()
{
    tlsClient.disconnect();
}

bool RpcClient::call(
    const std::string &method,
    const uint8_t *request,
    size_t requestSize,
    uint8_t *response,
    size_t responseSize)
{
    if (request == nullptr || response == nullptr)
    {
        return false;
    }

    // --------------------------------
    // Send method name length
    // --------------------------------

    uint32_t methodLength =
        static_cast<uint32_t>(method.size());

    if (!tlsClient.send(
            reinterpret_cast<const unsigned char *>(&methodLength),
            sizeof(methodLength)))
    {
        return false;
    }

    // --------------------------------
    // Send method name
    // --------------------------------

    if (!method.empty())
    {
        if (!tlsClient.send(
                reinterpret_cast<const unsigned char *>(method.data()),
                method.size()))
        {
            return false;
        }
    }

    // --------------------------------
    // Send request size
    // --------------------------------

    uint32_t requestLength =
        static_cast<uint32_t>(requestSize);

    if (!tlsClient.send(
            reinterpret_cast<const unsigned char *>(&requestLength),
            sizeof(requestLength)))
    {
        return false;
    }

    // --------------------------------
    // Send request payload
    // --------------------------------

    if (requestSize > 0)
    {
        if (!tlsClient.send(
                request,
                requestSize))
        {
            return false;
        }
    }

    // --------------------------------
    // Receive response
    //
    // For now we use responseSize.
    // Later the server will send the
    // actual response length.
    // --------------------------------

    size_t received = 0;

    while (received < responseSize)
    {
        int ret = tlsClient.receive(
            response + received,
            responseSize - received);

        if (ret <= 0)
        {
            return false;
        }

        received += static_cast<size_t>(ret);
    }

    return true;
}