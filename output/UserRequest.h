#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    int32_t id;
} UserRequest;

void serializeUserRequest(const UserRequest* object, uint8_t* buffer);
void deserializeUserRequest(UserRequest* object, const uint8_t* buffer);
