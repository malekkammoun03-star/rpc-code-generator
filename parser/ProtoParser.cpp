#include "ProtoParser.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::vector<Message> ProtoParser::parse(const std::string &filename)
{
    std::vector<Message> messages;
    services.clear();

    Message currentMessage;

    Service currentService;
    bool insideService = false;

    std::ifstream file(filename);

    if (!file)
    {
        std::cout << "Cannot open file" << std::endl;
        return messages;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        if (line.find("syntax") != std::string::npos)
            continue;

        if (line.find("service") != std::string::npos)
        {

            if (!currentService.name.empty())
            {
                services.push_back(currentService);
                currentService = Service();
            }

            std::stringstream ss(line);

            std::string keyword;

            ss >> keyword;
            ss >> currentService.name;

            insideService = true;

            continue;
        }
        if (insideService && line.find("rpc") != std::string::npos)
        {
            RpcMethod method;

            std::stringstream ss(line);

            std::string keyword;
            std::string methodAndRequest;
            std::string returnsKeyword;
            std::string responseToken;

            ss >> keyword;
            ss >> methodAndRequest;
            ss >> returnsKeyword;
            ss >> responseToken;

            size_t openParen = methodAndRequest.find('(');
            size_t closeParen = methodAndRequest.find(')');

            if (openParen != std::string::npos &&
                closeParen != std::string::npos)
            {
                method.name = methodAndRequest.substr(0, openParen);

                method.requestType = methodAndRequest.substr(
                    openParen + 1,
                    closeParen - openParen - 1);
            }

            if (!responseToken.empty() &&
                responseToken.front() == '(')
            {
                responseToken.erase(0, 1);
            }

            while (!responseToken.empty() &&
                   (responseToken.back() == ')' ||
                    responseToken.back() == ';'))
            {
                responseToken.pop_back();
            }

            method.responseType = responseToken;

            currentService.methods.push_back(method);

            continue;
        }

        if (insideService && line.find("}") != std::string::npos)
        {
            if (!currentService.name.empty())
            {
                services.push_back(currentService);
                currentService = Service();
            }

            insideService = false;

            continue;
        }

        if (line.find("{") != std::string::npos)
            continue;

        if (line.find("message") != std::string::npos)
        {
            if (!currentMessage.name.empty())
            {
                messages.push_back(currentMessage);
                currentMessage = Message();
            }

            std::stringstream ss(line);

            std::string keyword;

            ss >> keyword;
            ss >> currentMessage.name;

            continue;
        }

        Field field;

        std::stringstream ss(line);

        std::string equalSign;
        std::string numberToken;

        ss >> field.type;
        ss >> field.name;
        ss >> equalSign;
        ss >> numberToken;

        if (field.type.empty() ||
            field.name.empty() ||
            numberToken.empty())
        {
            continue;
        }

        if (!numberToken.empty() && numberToken.back() == ';')
            numberToken.pop_back();

        try
        {
            field.number = std::stoi(numberToken);
        }
        catch (...)
        {
            continue;
        }

        currentMessage.fields.push_back(field);
    }

    if (!currentMessage.name.empty())
    {
        messages.push_back(currentMessage);
    }

    if (!currentService.name.empty())
    {
        services.push_back(currentService);
    }

    for (const auto &msg : messages)
    {
        std::cout << "\nMessage: " << msg.name << std::endl;

        for (const auto &field : msg.fields)
        {
            std::cout << "Type   : " << field.type << std::endl;
            std::cout << "Name   : " << field.name << std::endl;
            std::cout << "Number : " << field.number << std::endl;
            std::cout << "------------------" << std::endl;
        }
    }

    for (const auto &service : services)
    {
        std::cout << "\nService: " << service.name << std::endl;

        for (const auto &method : service.methods)
        {
            std::cout << "RPC Method: " << method.name << std::endl;
            std::cout << "Request   : " << method.requestType << std::endl;
            std::cout << "Response  : " << method.responseType << std::endl;
            std::cout << "------------------" << std::endl;
        }
    }

    return messages;
}

const std::vector<Service> &ProtoParser::getServices() const
{
    return services;
}