#include <string.h>
#include "Company.h"

void serializeCompany(const Company* object, uint8_t* buffer)
{
    memcpy(buffer, object->companyName, 256);
    buffer += 256;

    memcpy(buffer, &object->employees, sizeof(uint64_t));
    buffer += sizeof(uint64_t);

    memcpy(buffer, &object->revenue, sizeof(float));
    buffer += sizeof(float);

}

void deserializeCompany(Company* object, const uint8_t* buffer)
{
    memcpy(object->companyName, buffer, 256);
    buffer += 256;

    memcpy(&object->employees, buffer, sizeof(uint64_t));
    buffer += sizeof(uint64_t);

    memcpy(&object->revenue, buffer, sizeof(float));
    buffer += sizeof(float);

}
