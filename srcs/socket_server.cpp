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
        shared_ptr<connection_handler> con(new connection_handler(_listener.accept()));
        _connections.push_back(con);
        connection c = { .id = con->get_id(), .hostname = con->get_hostname() };
        _connection_subscribers.notify(std::make_pair(c, response(con)));
        return ;
    }

    std::vector<shared_ptr<connection_handler> >::iterator it = std::find(_connections.begin(), _connections.end(), event.fd);
    if (it == _connections.end())
        return ;

    shared_ptr<connection_handler> con = *it;

    if (event.revents & ( POLLERR | POLLHUP | POLLNVAL ))
    {
        con->close();
        _disconnection_subscribers.notify(con->get_id());
        _connections.erase(it);
        return ;
    }

    if (event.revents & POLLIN)
    {
        std::vector<message> msgs = con->read();
        for (std::vector<message>::iterator msg = msgs.begin(); msg != msgs.end(); ++msg)
        {
            request req = { .id = con->get_id(), .message = *msg };
            _message_subscribers.notify(std::make_pair(req, response(con)));
        }
    }

    if (con->queued())
        con->flush();

    if (con->closing || con->full())
    {
        con->close();
        _disconnection_subscribers.notify(con->get_id());
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
