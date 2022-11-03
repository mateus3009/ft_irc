#include "context.hpp"

void create_irc_context(const char* port)
{
    socket_listener listener(port);
    socket_server   server(listener);

    file_descriptor_monitor monitor;
    monitor.add(listener);

    event_observer event_subscription(server);
    monitor.subscribe(&event_subscription);

    client_store client_s;

    connection_observer connection_subscription(monitor, client_s);
    server.subscribe_to_connection(&connection_subscription);

    disconnection_observer  disconnection_subscription(monitor, client_s);
    server.subscribe_to_disconnection(&disconnection_subscription);

    help help_command(client_s);

    router r;
    r.add("HELP", &help_command);

    message_observer message_subscription(&r);
    server.subscribe_to_message(&message_subscription);

    monitor.listen();
}
