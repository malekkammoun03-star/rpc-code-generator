#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    char companyName[256];
    uint64_t employees;
    float revenue;
} Company;

void serializeCompany(const Company* object, uint8_t* buffer);
void deserializeCompany(Company* object, const uint8_t* buffer);
