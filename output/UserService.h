#pragma once

#include "RpcClient.h"
#include "UserRequest.h"
#include "UserResponse.h"

class UserServiceClient
{
public:
    UserServiceClient(
        const std::string& host,
        int port);

    ~UserServiceClient();

    UserResponse GetUser(UserRequest request);

private:
    RpcClient client;
};
