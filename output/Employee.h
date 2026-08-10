#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    int32_t id;
    char company[256];
    bool manager;
} Employee;

void serializeEmployee(const Employee* message, uint8_t* buffer);
void deserializeEmployee(Employee* message, const uint8_t* buffer);
