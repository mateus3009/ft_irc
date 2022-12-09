#include "irc/Server.hpp"

int main(int argc, char** argv)
{
    try
    {
        char* port = (char *)"0";
        if (argc > 1)
            port = argv[1];

        char* password = (char *)"";
        if (argc > 2)
            password = argv[2];

        Server s(port, password);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
};
