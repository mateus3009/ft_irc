#include "client.hpp"

void client_store::add(const socket_connection& client)
{
    _clients.push_back(client);
    _newConnection.notify(client);
}

void client_store::remove(const socket_connection& client)
{
    std::vector<socket_connection>::iterator it;

    it = _clients.begin();
    while (it != _clients.end())
    {
        if (it->get_id() == client.get_id())
        {
            it->close();
            _clients.erase(it);
            _newDisconnection.notify(client);
        }
        else
            ++it;
    }
}

socket_connection client_store::find(const int& fd)
{
    std::vector<socket_connection>::iterator it;

    for (it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->get_id() == fd)
            return *it;
    }
    throw std::runtime_error("Client not found!");
}

void client_store::subscribe_new_connection(observer<socket_connection>* observer)
{
    if (observer != NULL)
        _newConnection.subscribe(observer);
}

void client_store::notify_new_connection(socket_connection value)
{
    _newConnection.notify(value);
}

void client_store::subscribe_new_disconnection(observer<socket_connection>* observer)
{
    if (observer != NULL)
        _newDisconnection.subscribe(observer);
}

void client_store::notify_new_disconnection(socket_connection value)
{
    _newDisconnection.notify(value);
}

std::vector<socket_connection>::const_iterator client_store::begin(void) const
{
    return _clients.begin();
}

std::vector<socket_connection>::const_iterator client_store::end(void) const
{
    return _clients.end();
}
