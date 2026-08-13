#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct
{
    int32_t id;
} UserRequest;

size_t serializeUserRequest(const UserRequest* object, uint8_t* buffer);
void deserializeUserRequest(UserRequest* object, const uint8_t* buffer);
