#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    char name[256];
} UserResponse;

void serializeUserResponse(const UserResponse* object, uint8_t* buffer);
void deserializeUserResponse(UserResponse* object, const uint8_t* buffer);
