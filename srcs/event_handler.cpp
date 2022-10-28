#include "event_handler.hpp"

new_connection_handler::new_connection_handler(const socket_listener& listener, client_store* clientStore) : _listener(listener), _clientStore(clientStore) {}

void new_connection_handler::handle(pollfd& event)
{
    if (_listener.get_id() != event.fd)
        return;

    socket_connection client(_listener.accept());
    client.send("Hello you!\n", 12);
    _clientStore->add(client);
}

new_data_handler::new_data_handler(client_store* clientStore) : _clientStore(clientStore), _channel() {}

void new_data_handler::handle(pollfd&)
{
}

void new_data_handler::send_to_everyone(const socket_connection& client, const char* data, size_t len) const
{
    std::vector<socket_connection>::const_iterator it = _clientStore->begin();
    while (it != _clientStore->end())
    {
        try
        {
            if (it->get_id() != client.get_id())
                it->send(data, len);
            ++it;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error when sending data to " << it->get_id() << std::endl;
            _clientStore->remove(*it);
        }
    }
}

new_socket_connection_handler::new_socket_connection_handler(event_listener* event_listener) : _event_listener(event_listener) {}

void new_socket_connection_handler::handle(socket_connection& socket)
{
    _event_listener->add(socket.get_id());
}

new_socket_disconnection_handler::new_socket_disconnection_handler(event_listener* event_listener) : _event_listener(event_listener) {}

void new_socket_disconnection_handler::handle(socket_connection& socket)
{
    std::cout << socket.get_id() << " is leaving us! :(" << std::endl;
    _event_listener->remove(socket.get_id());
}
