#include "channel.hpp"

channel::channel(void) : _name(), _clients() {}

channel::channel(const channel& other) : _name(other._name), _clients(other._clients) {}

channel::~channel() {}

channel& channel::operator=(const channel& other)
{
    _name       = other._name;
    _clients    = other._clients;
    return *this;
}

std::string channel::getName(void) const
{
    return _name;
}

void channel::add(const socket_connection& client)
{
    _clients.push_back(client);
}

void channel::remove(const socket_connection& client)
{
    std::vector<socket_connection>::iterator it;

    it = _clients.begin();
    while (it != _clients.end())
    {
        if (it->get_id() == client.get_id())
        {
            _clients.erase(it);
        }
        else
            ++it;
    }
}

void channel::broadcast(const socket_connection& client, const message& msg) const
{
    std::vector<socket_connection>::const_iterator it = _clients.begin();
    while (it != _clients.end())
    {
        try
        {
            if (it->get_id() != client.get_id())
                it->send(msg.params.begin()->c_str(), msg.params.begin()->length());
            ++it;
        }
        catch(const std::exception& e)
        {
            continue ;
        }
    }
}
