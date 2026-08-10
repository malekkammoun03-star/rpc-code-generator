#include "CodeGenerator.h"
#include <fstream>
#include <iostream>
void CodeGenerator::generate(const Message &message)
{
    std::string headerName = "../output/" + message.name + ".h";
    std::string sourceName = "../output/" + message.name + ".c";

    std::ofstream file(headerName);
    std::ofstream sourceFile(sourceName);
    if (!sourceFile)
    {
        std::cout << "Cannot create source file" << std::endl;
        return;
    }
    if (!file)
    {
        std::cout << "Cannot create file\n";
        return;
    }
    file << "#pragma once\n\n";
    file << "#include <stdint.h>\n";
    file << "#include <stdbool.h>\n\n";
    file << "typedef struct\n";
    file << "{\n";
    for (const auto &field : message.fields)
    {
        if (field.type == "int32")
            file << "    int32_t " << field.name << ";\n";

        else if (field.type == "uint64")
            file << "    uint64_t " << field.name << ";\n";

        else if (field.type == "bool")
            file << "    bool " << field.name << ";\n";

        else if (field.type == "float")
            file << "    float " << field.name << ";\n";

        else if (field.type == "double")
            file << "    double " << field.name << ";\n";

        else if (field.type == "string")
            file << "    char " << field.name << "[256];\n";
    }
    file << "} " << message.name << ";\n\n";
    file << "void serialize" << message.name
         << "(const " << message.name
         << "* object, uint8_t* buffer);\n";

    file << "void deserialize" << message.name
         << "(" << message.name
         << "* object, const uint8_t* buffer);\n";
    sourceFile << "#include <string.h>\n";
    sourceFile << "#include \"" << message.name << ".h\"\n\n";
    sourceFile << "void serialize"
               << message.name
               << "(const "
               << message.name
               << "* object, uint8_t* buffer)\n";
    sourceFile << "{\n";
    for (const auto &field : message.fields)
    {
        if (field.type == "int32")
        {
            sourceFile << "    memcpy(buffer, &object->"
                       << field.name
                       << ", sizeof(int32_t));\n";

            sourceFile << "    buffer += sizeof(int32_t);\n\n";
        }
        else if (field.type == "bool")
        {
            sourceFile << "    memcpy(buffer, &object->"
                       << field.name
                       << ", sizeof(bool));\n";

            sourceFile << "    buffer += sizeof(bool);\n\n";
        }
        else if (field.type == "float")
        {
            sourceFile << "    memcpy(buffer, &object->"
                       << field.name
                       << ", sizeof(float));\n";

            sourceFile << "    buffer += sizeof(float);\n\n";
        }
        else if (field.type == "double")
        {
            sourceFile << "    memcpy(buffer, &object->"
                       << field.name
                       << ", sizeof(double));\n";

            sourceFile << "    buffer += sizeof(double);\n\n";
        }
        else if (field.type == "uint64")
        {
            sourceFile << "    memcpy(buffer, &object->"
                       << field.name
                       << ", sizeof(uint64_t));\n";

            sourceFile << "    buffer += sizeof(uint64_t);\n\n";
        }
        else if (field.type == "string")
        {
            sourceFile << "    memcpy(buffer, object->"
                       << field.name
                       << ", 256);\n";

            sourceFile << "    buffer += 256;\n\n";
        }
    }
    sourceFile << "}\n\n";
    sourceFile << "void deserialize"
               << message.name
               << "("
               << message.name
               << "* object, const uint8_t* buffer)\n";
    sourceFile << "{\n";
    for (const auto &field : message.fields)
    {
        if (field.type == "int32")
        {
            sourceFile << "    memcpy(&object->"
                       << field.name
                       << ", buffer, sizeof(int32_t));\n";

            sourceFile << "    buffer += sizeof(int32_t);\n\n";
        }
        else if (field.type == "bool")
        {
            sourceFile << "    memcpy(&object->"
                       << field.name
                       << ", buffer, sizeof(bool));\n";

            sourceFile << "    buffer += sizeof(bool);\n\n";
        }
        else if (field.type == "float")
        {
            sourceFile << "    memcpy(&object->"
                       << field.name
                       << ", buffer, sizeof(float));\n";

            sourceFile << "    buffer += sizeof(float);\n\n";
        }
        else if (field.type == "double")
        {
            sourceFile << "    memcpy(&object->"
                       << field.name
                       << ", buffer, sizeof(double));\n";

            sourceFile << "    buffer += sizeof(double);\n\n";
        }
        else if (field.type == "uint64")
        {
            sourceFile << "    memcpy(&object->"
                       << field.name
                       << ", buffer, sizeof(uint64_t));\n";

            sourceFile << "    buffer += sizeof(uint64_t);\n\n";
        }
        else if (field.type == "string")
        {
            sourceFile << "    memcpy(object->"
                       << field.name
                       << ", buffer, 256);\n";

            sourceFile << "    buffer += 256;\n\n";
        }
    }
    sourceFile << "}\n";
}
void CodeGenerator::generateService(const Service &service)
{
    std::string fileName = "output/" + service.name + ".h";

    std::ofstream file(fileName);

    if (!file)
    {
        std::cout << "Cannot create service file" << std::endl;
        return;
    }

    file << "#pragma once\n\n";

    // Include request and response message headers
    for (const auto &method : service.methods)
    {
        file << "#include \"" << method.requestType << ".h\"\n";
        file << "#include \"" << method.responseType << ".h\"\n";
    }

    file << "\n";

    // Generate RPC method declarations
    for (const auto &method : service.methods)
    {
        file << method.responseType
             << " "
             << method.name
             << "("
             << method.requestType
             << " request);\n";
    }

    file.close();
}