#include <string.h>
#include "UserResponse.h"

size_t serializeUserResponse(const UserResponse* object, uint8_t* buffer)
{
    size_t offset = 0;

    memcpy(buffer + offset, object->name, 256);
    offset += 256;

    return offset;
}

void deserializeUserResponse(UserResponse* object, const uint8_t* buffer)
{
    size_t offset = 0;

    memcpy(object->name, buffer + offset, 256);
    offset += 256;

}
