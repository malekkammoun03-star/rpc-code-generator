#pragma once

#include "TlsClient.h"
#include <cstddef>
#include <cstdint>
#include <string>

class RpcClient
{
public:
    RpcClient();
    ~RpcClient();

    bool connect(const std::string &host, int port);
    void disconnect();

    bool call(
        const std::string &method,
        const uint8_t *request,
        size_t requestSize,
        uint8_t *response,
        size_t responseSize);

private:
    TlsClient tlsClient;
};