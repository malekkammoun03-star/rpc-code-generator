#include "UserService.h"

#include <cstdint>
#include <cstddef>

UserServiceClient::UserServiceClient(
    const std::string& host,
    int port)
{
    client.connect(host, port);
}

UserServiceClient::~UserServiceClient()
{
    client.disconnect();
}

UserResponse UserServiceClient::GetUser(UserRequest request)
{
    UserResponse response{};

    uint8_t requestBuffer[4096]{};
    uint8_t responseBuffer[4096]{};

    size_t requestSize =
        serializeUserRequest(&request, requestBuffer);

    client.call(
        "GetUser",
        requestBuffer,
        requestSize,
        responseBuffer,
        sizeof(responseBuffer));

    deserializeUserResponse(&response, responseBuffer);

    return response;
}

