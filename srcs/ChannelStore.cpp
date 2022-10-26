#include "ChannelStore.hpp"

IrcChannel::IrcChannel(void) : _name(), _clients() {}

IrcChannel::IrcChannel(const IrcChannel& other) : _name(other._name), _clients(other._clients) {}

IrcChannel::~IrcChannel() {}

IrcChannel& IrcChannel::operator=(const IrcChannel& other)
{
    _name       = other._name;
    _clients    = other._clients;
    return *this;
}

void IrcChannel::add(const SocketConnection& client)
{
    _clients.push_back(client);
}

void IrcChannel::remove(const SocketConnection& client)
{
    std::vector<SocketConnection>::iterator it;

    it = _clients.begin();
    while (it != _clients.end())
    {
        if (it->getId() == client.getId())
        {
            _clients.erase(it);
        }
        else
            ++it;
    }
}

void IrcChannel::broadcast(const SocketConnection& client, const IrcMessage& msg)
{
    std::vector<SocketConnection>::const_iterator it = _clients.begin();
    while (it != _clients.end())
    {
        try
        {
            if (it->getId() != client.getId())
                it->send(msg.params.begin()->c_str(), msg.params.begin()->length());
            ++it;
        }
        catch(const std::exception& e)
        {
            continue ;
        }
    }
}
