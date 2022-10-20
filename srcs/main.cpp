#include <iostream>
#include <sstream>
#include "EventListener.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return (1);
    }

    SocketListener  server(argv[1]);
    EventListener   listener(server);
    listener.listen();

    return (0);
}
