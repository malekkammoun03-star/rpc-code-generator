#include "CodeGenerator.h"

#include <fstream>
#include <iostream>

void CodeGenerator::generate(const Message &message)
{
    std::string headerName = "output/" + message.name + ".h";
    std::string sourceName = "output/" + message.name + ".c";

    std::ofstream file(headerName);
    std::ofstream sourceFile(sourceName);

    if (!file)
    {
        std::cout << "Cannot create header file" << std::endl;
        return;
    }

    if (!sourceFile)
    {
        std::cout << "Cannot create source file" << std::endl;
        return;
    }

    // =========================
    // Generate header
    // =========================

    file << "#pragma once\n\n";
    file << "#include <stdint.h>\n";
    file << "#include <stdbool.h>\n";
    file << "#include <stddef.h>\n\n";

    file << "typedef struct\n";
    file << "{\n";

    for (const auto &field : message.fields)
    {
        if (field.type == "int32")
        {
            file << "    int32_t " << field.name << ";\n";
        }
        else if (field.type == "uint64")
        {
            file << "    uint64_t " << field.name << ";\n";
        }
        else if (field.type == "bool")
        {
            file << "    bool " << field.name << ";\n";
        }
        else if (field.type == "float")
        {
            file << "    float " << field.name << ";\n";
        }
        else if (field.type == "double")
        {
            file << "    double " << field.name << ";\n";
        }
        else if (field.type == "string")
        {
            file << "    char " << field.name << "[256];\n";
        }
    }

    file << "} " << message.name << ";\n\n";

    file << "size_t serialize" << message.name
         << "(const " << message.name
         << "* object, uint8_t* buffer);\n";

    file << "void deserialize" << message.name
         << "(" << message.name
         << "* object, const uint8_t* buffer);\n";

    // =========================
    // Generate source
    // =========================

    sourceFile << "#include <string.h>\n";
    sourceFile << "#include \"" << message.name << ".h\"\n\n";

    // =========================
    // Serialize function
    // =========================

    sourceFile << "size_t serialize"
               << message.name
               << "(const "
               << message.name
               << "* object, uint8_t* buffer)\n";

    sourceFile << "{\n";
    sourceFile << "    size_t offset = 0;\n\n";

    for (const auto &field : message.fields)
    {
        if (field.type == "int32")
        {
            sourceFile << "    memcpy(buffer + offset, &object->"
                       << field.name
                       << ", sizeof(int32_t));\n";

            sourceFile << "    offset += sizeof(int32_t);\n\n";
        }
        else if (field.type == "uint64")
        {
            sourceFile << "    memcpy(buffer + offset, &object->"
                       << field.name
                       << ", sizeof(uint64_t));\n";

            sourceFile << "    offset += sizeof(uint64_t);\n\n";
        }
        else if (field.type == "bool")
        {
            sourceFile << "    memcpy(buffer + offset, &object->"
                       << field.name
                       << ", sizeof(bool));\n";

            sourceFile << "    offset += sizeof(bool);\n\n";
        }
        else if (field.type == "float")
        {
            sourceFile << "    memcpy(buffer + offset, &object->"
                       << field.name
                       << ", sizeof(float));\n";

            sourceFile << "    offset += sizeof(float);\n\n";
        }
        else if (field.type == "double")
        {
            sourceFile << "    memcpy(buffer + offset, &object->"
                       << field.name
                       << ", sizeof(double));\n";

            sourceFile << "    offset += sizeof(double);\n\n";
        }
        else if (field.type == "string")
        {
            sourceFile << "    memcpy(buffer + offset, object->"
                       << field.name
                       << ", 256);\n";

            sourceFile << "    offset += 256;\n\n";
        }
    }

    sourceFile << "    return offset;\n";
    sourceFile << "}\n\n";

    // =========================
    // Deserialize function
    // =========================

    sourceFile << "void deserialize"
               << message.name
               << "("
               << message.name
               << "* object, const uint8_t* buffer)\n";

    sourceFile << "{\n";
    sourceFile << "    size_t offset = 0;\n\n";

    for (const auto &field : message.fields)
    {
        if (field.type == "int32")
        {
            sourceFile << "    memcpy(&object->"
                       << field.name
                       << ", buffer + offset, sizeof(int32_t));\n";

            sourceFile << "    offset += sizeof(int32_t);\n\n";
        }
        else if (field.type == "uint64")
        {
            sourceFile << "    memcpy(&object->"
                       << field.name
                       << ", buffer + offset, sizeof(uint64_t));\n";

            sourceFile << "    offset += sizeof(uint64_t);\n\n";
        }
        else if (field.type == "bool")
        {
            sourceFile << "    memcpy(&object->"
                       << field.name
                       << ", buffer + offset, sizeof(bool));\n";

            sourceFile << "    offset += sizeof(bool);\n\n";
        }
        else if (field.type == "float")
        {
            sourceFile << "    memcpy(&object->"
                       << field.name
                       << ", buffer + offset, sizeof(float));\n";

            sourceFile << "    offset += sizeof(float);\n\n";
        }
        else if (field.type == "double")
        {
            sourceFile << "    memcpy(&object->"
                       << field.name
                       << ", buffer + offset, sizeof(double));\n";

            sourceFile << "    offset += sizeof(double);\n\n";
        }
        else if (field.type == "string")
        {
            sourceFile << "    memcpy(object->"
                       << field.name
                       << ", buffer + offset, 256);\n";

            sourceFile << "    offset += 256;\n\n";
        }
    }

    sourceFile << "}\n";
}

// ============================================================
// Generate RPC Service Client
// ============================================================

void CodeGenerator::generateService(const Service &service)
{
    std::string headerName = "output/" + service.name + ".h";
    std::string sourceName = "output/" + service.name + ".cpp";

    std::ofstream header(headerName);
    std::ofstream source(sourceName);

    if (!header)
    {
        std::cout << "Cannot create service header file"
                  << std::endl;
        return;
    }

    if (!source)
    {
        std::cout << "Cannot create service source file"
                  << std::endl;
        return;
    }

    // =========================
    // Generate header
    // =========================

    header << "#pragma once\n\n";

    header << "#include \"RpcClient.h\"\n";

    for (const auto &method : service.methods)
    {
        header << "#include \""
               << method.requestType
               << ".h\"\n";

        header << "#include \""
               << method.responseType
               << ".h\"\n";
    }

    header << "\n";

    header << "class "
           << service.name
           << "Client\n";

    header << "{\n";
    header << "public:\n";

    header << "    "
           << service.name
           << "Client(\n";

    header << "        const std::string& host,\n";
    header << "        int port);\n\n";

    header << "    ~"
           << service.name
           << "Client();\n\n";

    for (const auto &method : service.methods)
    {
        header << "    "
               << method.responseType
               << " "
               << method.name
               << "("
               << method.requestType
               << " request);\n";
    }

    header << "\nprivate:\n";

    header << "    RpcClient client;\n";

    header << "};\n";

    // =========================
    // Generate source
    // =========================

    source << "#include \""
           << service.name
           << ".h\"\n\n";

    source << "#include <cstdint>\n";
    source << "#include <cstddef>\n\n";

    source << service.name
           << "Client::"
           << service.name
           << "Client(\n";

    source << "    const std::string& host,\n";
    source << "    int port)\n";

    source << "{\n";

    source << "    client.connect(host, port);\n";

    source << "}\n\n";

    source << service.name
           << "Client::~"
           << service.name
           << "Client()\n";

    source << "{\n";

    source << "    client.disconnect();\n";

    source << "}\n\n";

    // =========================
    // Generate RPC methods
    // =========================

    for (const auto &method : service.methods)
    {
        source << method.responseType
               << " "
               << service.name
               << "Client::"
               << method.name
               << "("
               << method.requestType
               << " request)\n";

        source << "{\n";

        source << "    "
               << method.responseType
               << " response{};\n\n";

        source << "    uint8_t requestBuffer[4096]{};\n";
        source << "    uint8_t responseBuffer[4096]{};\n\n";

        // Serialize request and get exact size
        source << "    size_t requestSize =\n";

        source << "        serialize"
               << method.requestType
               << "(&request, requestBuffer);\n\n";

        // RPC call
        source << "    client.call(\n";

        source << "        \""
               << method.name
               << "\",\n";

        source << "        requestBuffer,\n";
        source << "        requestSize,\n";

        source << "        responseBuffer,\n";
        source << "        sizeof(responseBuffer));\n\n";

        // Deserialize response
        source << "    deserialize"
               << method.responseType
               << "(&response, responseBuffer);\n\n";

        source << "    return response;\n";

        source << "}\n\n";
    }

    header.close();
    source.close();
}