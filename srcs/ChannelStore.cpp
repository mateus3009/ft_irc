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

std::string IrcChannel::getName(void) const
{
    return _name;
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

void IrcChannel::broadcast(const SocketConnection& client, const IrcMessage& msg) const
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

ChannelStore::ChannelStore(void) : _channels() {}

ChannelStore::ChannelStore(const ChannelStore& other) : _channels(other._channels) {}

ChannelStore::~ChannelStore() {}

ChannelStore& ChannelStore::operator=(const ChannelStore& other)
{
    _channels = other._channels;
    return *this;
}

IrcChannel& ChannelStore::find(const std::string& channel)
{
    std::vector<IrcChannel>::iterator it;

    it = _channels.begin();
    while (it != _channels.end())
    {
        if (it->getName() == channel)
            return *it;
        ++it;
    }

    throw std::runtime_error("Channel not found!");
}
