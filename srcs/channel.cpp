#include "channel.hpp"

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
			this->broadcast(client, "cliente tanana leave group");
        }
        else
            ++it;
    }
}

void channel::broadcast(const socket_connection& client, const std::string &msg) const
{
    std::vector<socket_connection>::const_iterator it = _clients.begin();
    while (it != _clients.end())
    {
        try
        {
            if (it->get_id() != client.get_id())
                it->send(msg.c_str(), msg.length());
            ++it;
        }
        catch(const std::exception& e)
        {
            continue ;
        }
    }
}