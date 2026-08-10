#include "parser/ProtoParser.h"
#include "generator/CodeGenerator.h"
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: app <proto file>\n";
        return 1;
    }

    ProtoParser parser;

    std::vector<Message> messages = parser.parse(argv[1]);

    CodeGenerator generator;

    for (const auto &message : messages)
    {
        generator.generate(message);
    }

    for (const auto &service : parser.getServices())
    {
        generator.generateService(service);
    }

    return 0;
}