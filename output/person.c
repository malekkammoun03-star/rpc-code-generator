#include <string.h>
#include "Person.h"

void serializePerson(const Person* object, uint8_t* buffer)
{
    memcpy(buffer, &object->id, sizeof(int32_t));
    buffer += sizeof(int32_t);

    memcpy(buffer, object->name, 256);
    buffer += 256;

    memcpy(buffer, &object->active, sizeof(bool));
    buffer += sizeof(bool);

}

void deserializePerson(Person* object, const uint8_t* buffer)
{
    memcpy(&object->id, buffer, sizeof(int32_t));
    buffer += sizeof(int32_t);

    memcpy(object->name, buffer, 256);
    buffer += 256;

    memcpy(&object->active, buffer, sizeof(bool));
    buffer += sizeof(bool);

}
