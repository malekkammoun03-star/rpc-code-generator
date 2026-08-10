#pragma once
#include <vector>
#include <string>
#include "Field.h"
struct Message
{
    std::string name;
    std::vector<Field> fields;
};