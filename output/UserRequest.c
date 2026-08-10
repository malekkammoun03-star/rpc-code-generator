#include <string.h>
#include "UserRequest.h"

void serializeUserRequest(const UserRequest* object, uint8_t* buffer)
{
    memcpy(buffer, &object->id, sizeof(int32_t));
    buffer += sizeof(int32_t);

}

void deserializeUserRequest(UserRequest* object, const uint8_t* buffer)
{
    memcpy(&object->id, buffer, sizeof(int32_t));
    buffer += sizeof(int32_t);

}
