#include <string.h>
#include "Employee.h"

void serializeEmployee(const Employee* object, uint8_t* buffer)
{
    memcpy(buffer, &object->id, sizeof(int32_t));
    buffer += sizeof(int32_t);

    memcpy(buffer, object->company, 256);
    buffer += 256;

    memcpy(buffer, &object->manager, sizeof(bool));
    buffer += sizeof(bool);

}

void deserializeEmployee(Employee* object, const uint8_t* buffer)
{
    memcpy(&object->id, buffer, sizeof(int32_t));
    buffer += sizeof(int32_t);

    memcpy(object->company, buffer, 256);
    buffer += 256;

    memcpy(&object->manager, buffer, sizeof(bool));
    buffer += sizeof(bool);

}
