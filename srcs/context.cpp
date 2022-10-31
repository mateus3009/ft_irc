#include "context.hpp"

void create_irc_context(const char* port)
{
    socket_listener listener(port);
    socket_server   server(listener);

    file_descriptor_monitor monitor;
    monitor.add(listener);

    event_observer event_subscription(server);
    monitor.subscribe(&event_subscription);

    connection_observer connection_subscription(monitor);
    server.subscribe_to_connection(&connection_subscription);

    disconnection_observer  disconnection_subscription(monitor);
    server.subscribe_to_disconnection(&disconnection_subscription);

    message_observer        message_subscription;
    server.subscribe_to_message(&message_subscription);

    monitor.listen();
}
