#include <iostream>
#include <sstream>
#include "Socket.hpp"
#include "EventListener.hpp"
#include "EventHandler.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return (1);
    }

    SocketListener  server(argv[1]);
    EventListener   listener;
    ClientStore     cs;
    NewConnectionHandler    nch(server, &cs);

    listener.add(server.getId());
    listener.subscribe(&nch);
    listener.listen();

    return (0);
}
