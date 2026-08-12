#include "TlsClient.h"
#include <iostream>

int main()
{
    TlsClient client;

    if (client.connect("example.com", 443))
    {
        std::cout << "TLS test successful!" << std::endl;

        client.disconnect();

        return 0;
    }

    std::cout << "TLS test failed." << std::endl;

    return 1;
}