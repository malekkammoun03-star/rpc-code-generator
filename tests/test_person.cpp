#include "../output/person.h"

#include <iostream>
#include <cstring>

int main()
{
    Person p;

    p.id = 25;

    strcpy(p.name, "Alice");

    p.active = true;

    p.salary = 5000.5f;

    p.temperature = 36.7;

    p.counter = 123456;

    uint8_t buffer[1024];

    serializePerson(&p, buffer);

    Person copy;

    deserializePerson(&copy, buffer);

    std::cout << "ID: " << copy.id << std::endl;
    std::cout << "Name: " << copy.name << std::endl;
    std::cout << "Active: " << copy.active << std::endl;
    std::cout << "Salary: " << copy.salary << std::endl;
    std::cout << "Temperature: " << copy.temperature << std::endl;
    std::cout << "Counter: " << copy.counter << std::endl;

    return 0;
}