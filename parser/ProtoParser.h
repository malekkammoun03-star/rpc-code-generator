#pragma once
#include <vector>
#include "Message.h"
#include "Service.h"

class ProtoParser
{
public:
    std::vector<Message> parse(const std::string &filename);
    const std::vector<Service> &getServices() const;

private:
    std::vector<Service> services;
};