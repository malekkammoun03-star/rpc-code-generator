#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    int32_t id;
    char name[256];
    bool active;
} Person;

void serializePerson(const Person* object, uint8_t* buffer);
void deserializePerson(Person* object, const uint8_t* buffer);
