#include <iostream>
#include <sstream>
#include "Socket.hpp"
#include "EventListener.hpp"
#include "EventHandler.hpp"
#include "IrcMessage.hpp"

void irc_context(const char* port)
{
    SocketListener                  server(port);
    EventListener                   listener;
    ClientStore                     cs;
    NewConnectionHandler            nch(server, &cs);
    NewDataHandler                  ndh(&cs);
    NewSocketConnectionHandler      nsch(&listener);
    NewSocketDisconnectionHandler   nsdh(&listener);

    listener.add(server.getId());
    listener.subscribe(&nch);
    listener.subscribe(&ndh);
    cs.subscribeNewConnection(&nsch);
    cs.subscribeNewDisconnection(&nsdh);
    listener.listen();
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return (1);
    }

    irc_context(argv[1]);

    return (0);
}
