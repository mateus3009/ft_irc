#include "socket_server.hpp"

socket_server::socket_server(socket_listener& listener) :
    _listener(listener),
    _connections(),
    _connection_subscribers(),
    _message_subscribers(),
    _disconnection_subscribers() {}

void socket_server::handle(pollfd& event)
{
    if (event.revents & POLLIN && event.fd == _listener.get_id())
    {
        connection_handler con(_listener.accept());
        _connections.push_back(con);
        connection c = { .id = con.get_id(), .hostname = con.get_hostname() };
        _connection_subscribers.notify(std::make_pair(c, con.get_response()));
        return ;
    }

    std::vector<connection_handler>::iterator it = std::find(_connections.begin(), _connections.end(), event.fd);
    if (it == _connections.end())
        return ;

    if (event.revents & ( POLLERR | POLLHUP | POLLNVAL ))
    {
        it->close();
        _disconnection_subscribers.notify(it->get_id());
        _connections.erase(it);
        return ;
    }

    if (event.revents & POLLIN)
    {
        std::vector<message> msgs = it->read();
        for (std::vector<message>::iterator msg = msgs.begin(); msg != msgs.end(); ++msg)
        {
            request req = { .id = it->get_id(), .message = *msg };
            _message_subscribers.notify(std::make_pair(req, it->get_response()));
        }
    }

    if (it->queued())
        it->flush();

    if (it->closing)
    {
        it->close();
        _disconnection_subscribers.notify(it->get_id());
        _connections.erase(it);
        return ;
    }

}

void socket_server::subscribe_to_connection(observer<std::pair<const connection, response> >* observer)
{
    if (observer != NULL)
        _connection_subscribers.subscribe(observer);
}

void socket_server::subscribe_to_message(observer<std::pair<const request, response> >* observer)
{
    if (observer != NULL)
        _message_subscribers.subscribe(observer);
}

void socket_server::subscribe_to_disconnection(observer<const int>* observer)
{
    if (observer != NULL)
        _disconnection_subscribers.subscribe(observer);
}
