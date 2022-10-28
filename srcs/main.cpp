#include <iostream>
#include <sstream>
#include "socket_listener.hpp"
#include "socket_connection.hpp"
#include "event_listener.hpp"
#include "event_handler.hpp"
#include "message.hpp"

# include "shared_ptr.hpp"
# include "either.hpp"
# include "optional.hpp"

void irc_context(const char* port)
{
    socket_listener                  server(port);
    event_listener                   listener;
    client_store                     cs;
    new_connection_handler            nch(server, &cs);
    new_data_handler                  ndh(&cs);
    new_socket_connection_handler      nsch(&listener);
    new_socket_disconnection_handler   nsdh(&listener);

    listener.add(server.get_id());
    listener.subscribe(&nch);
    listener.subscribe(&ndh);
    cs.subscribe_new_connection(&nsch);
    cs.subscribe_new_disconnection(&nsdh);
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
