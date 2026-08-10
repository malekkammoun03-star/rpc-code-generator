#pragma once

#include "Message.h"
#include "Service.h"

class CodeGenerator
{
public:
    void generate(const Message &message);
    void generateService(const Service &service);
};