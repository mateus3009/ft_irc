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
        connection_handler connection(_listener.accept());
        _connections.push_back(connection);
        _connection_subscribers.notify(std::make_pair(connection.get_id(), connection.get_response()));
        return ;
    }

    std::vector<connection_handler>::iterator it = std::find(_connections.begin(), _connections.end(), event.fd);
    if (it == _connections.end())
        return ;

    if (event.revents & POLLERR || event.revents & POLLHUP || event.revents & POLLNVAL)
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
            request req;
            req.id      = it->get_id();
            req.message = *msg;
            _message_subscribers.notify(std::make_pair(req, it->get_response()));
        }
    }

    if (event.revents & POLLOUT && it->queued())
    {
        it->flush();
        if (it->queued())
            event.events |= POLLOUT;
    }

    if (!it->queued())
        event.events = POLLIN;

    if (it->closing)
    {
        it->close();
        _disconnection_subscribers.notify(it->get_id());
        _connections.erase(it);
        return ;
    }

}

void socket_server::subscribe_to_connection(observer<std::pair<const int, response> >* observer)
{
    if (observer != NULL)
        _connection_subscribers.subscribe(observer);
}

void socket_server::subscribe_to_message(observer<std::pair<request, response> >* observer)
{
    if (observer != NULL)
        _message_subscribers.subscribe(observer);
}

void socket_server::subscribe_to_disconnection(observer<const int>* observer)
{
    if (observer != NULL)
        _disconnection_subscribers.subscribe(observer);
}
