#include <string.h>
#include "UserRequest.h"

size_t serializeUserRequest(const UserRequest* object, uint8_t* buffer)
{
    size_t offset = 0;

    memcpy(buffer + offset, &object->id, sizeof(int32_t));
    offset += sizeof(int32_t);

    return offset;
}

void deserializeUserRequest(UserRequest* object, const uint8_t* buffer)
{
    size_t offset = 0;

    memcpy(&object->id, buffer + offset, sizeof(int32_t));
    offset += sizeof(int32_t);

}
