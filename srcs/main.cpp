#include <iostream>
#include <sstream>
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

    std::string to("Hello you\n");
    client.send(to.c_str(), to.size() + 1);

    char    data[100];
    memset(data, 0, sizeof(data));
    client.receive(data, sizeof(data));

    std::cout << data << std::endl;

    return (0);
}
