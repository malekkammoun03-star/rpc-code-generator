#include <string.h>
#include "UserResponse.h"

void serializeUserResponse(const UserResponse* object, uint8_t* buffer)
{
    memcpy(buffer, object->name, 256);
    buffer += 256;

}

void deserializeUserResponse(UserResponse* object, const uint8_t* buffer)
{
    memcpy(object->name, buffer, 256);
    buffer += 256;

}
