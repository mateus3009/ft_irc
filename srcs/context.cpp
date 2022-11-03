#include "context.hpp"

void create_irc_context(const char* port, const char* password)
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

    router r;

    help help_command(client_s);
    r.add("HELP", &help_command);

    nick nick_command(client_s);
    r.add("NICK", &nick_command);

    pass pass_command(client_s, password);
    r.add("PASS", &pass_command);

    message_observer message_subscription(&r);
    server.subscribe_to_message(&message_subscription);

    monitor.listen();
}
