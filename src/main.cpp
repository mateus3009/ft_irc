#include "SocketServer.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <port> <password>" << std::endl;
        return (1);
    }

    SocketServer server(atoui(argv[1]));
    std::cout << " " << server.accept().getSocket() << std::endl;

    return (0);
}
