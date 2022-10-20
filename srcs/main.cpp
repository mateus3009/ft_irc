#include <iostream>
#include "Socket.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return (1);
    }

    SocketListener listener(argv[1]);

    SocketConnection client(listener.accept());

    return (0);
}
