#pragma once
#include <string>
#include <vector>
#include "RpcMethod.h"

struct Service
{
    std::string name;
    std::vector<RpcMethod> methods;
};