#include "irc/Channel.hpp"

/* Membership */

Membership::Membership(const shared_ptr<Client>& client, const unsigned int& modes) : Modes(modes), _client(client) {}

shared_ptr<Client> Membership::getClient(void) const { return _client; }

bool operator==(const Membership& l, const Membership& r)
{
    return l.getClient() == r.getClient();
}

bool operator==(const Membership& m, const Client& c)
{
    return m.getClient() == c;
}

bool operator<(const Membership& l, const Membership& r)
{
    return l.getClient() < r.getClient();
}

/* Channel */

Channel::Channel(const std::string& name, shared_ptr<Client> founder, ChannelStore& store) : Modes(MODE_CHANNEL_PROTECTED_TOPIC | MODE_CHANNEL_NO_EXTERNAL_MESSAGES), _name(name), _store(store)
{
    shared_ptr<Membership> membership = add(founder);
    membership->setModes(MODE_MEMBERSHIP_FOUNDER);
}

std::string Channel::getName(void) const { return _name; }

std::string Channel::getTopic(void) const { return _topic; }

void Channel::setTopic(const std::string& topic) { _topic = topic; }

std::string Channel::getKey(void) const { return _key; }

void Channel::setKey(const std::string& key) { _key = key; }

shared_ptr<Membership> Channel::add(shared_ptr<Client>& client)
{
    shared_ptr<Membership> membership = new Membership(client);
    if (!_memberships.insert(membership).second)
        throw Channel::ClientIsAlreadyAMemberException("The Client is already a member of this channel!");
    return membership;
}

shared_ptr<Membership> Channel::find(const shared_ptr<Client>& client)
{
    Channel::iterator it = std::find(_memberships.begin(), _memberships.end(), client);
    if (it == _memberships.end())
        throw Channel::ClientNotFoundException("The client is not a member of this channel!");
    return *it;
}

void Channel::remove(shared_ptr<Membership>& membership)
{
    Channel::iterator it = _memberships.find(membership);
    if (it == _memberships.end())
        throw Channel::ClientNotFoundException("The client is not a member of this channel!");

    _memberships.erase(membership);

    if (_memberships.empty())
        _store.remove(this);
}

void Channel::broadcast(const Message& msg)
{
    ClientMessageSender s = { .msg = msg };
    std::for_each(_memberships.begin(), _memberships.end(), s);
}

Channel::iterator Channel::begin(void) const { return _memberships.begin(); }

Channel::iterator Channel::end(void) const { return _memberships.end(); }

Channel::ClientIsAlreadyAMemberException::ClientIsAlreadyAMemberException(const char* what) : std::runtime_error(what) {}

Channel::ClientNotFoundException::ClientNotFoundException(const char* what) : std::runtime_error(what) {}

void Channel::ClientMessageSender::operator()(shared_ptr<Membership> membership)
{
    membership->getClient()->send(msg);
}

bool operator==(const Channel& l, const Channel& r)
{
    return iequals(l.getName(), r.getName());
}

bool operator==(const Channel& channel, const std::string& name)
{
    return iequals(channel.getName(), name);
}

bool operator<(const Channel& l, const Channel& r)
{
    return l.getName() < r.getName();
}

/* ChannelStore */

void ChannelStore::add(shared_ptr<Client> client, const std::string& name)
{
    shared_ptr<Channel> channel = new Channel(name, client, *this);
    if (!_channels.insert(channel).second)
        throw ChannelStore::ChannelAlreadyExistsException("Two channels cannot have the same name!");
}

shared_ptr<Channel> ChannelStore::find(const std::string& name)
{
    ChannelStore::iterator it = std::find(_channels.begin(), _channels.end(), name);
    if (it == _channels.end())
        throw ChannelStore::ChannelNotFoundException("There is no channel with this name!");
    return *it;
}

void ChannelStore::remove(const shared_ptr<Channel>& channel)
{
    if (_channels.erase(channel) == 0)
        throw ChannelStore::ChannelNotFoundException("The channel does not exists!");
}

ChannelStore::iterator ChannelStore::begin(void) const { return _channels.begin(); }

ChannelStore::iterator ChannelStore::end(void) const { return _channels.end(); }

ChannelStore::ChannelAlreadyExistsException::ChannelAlreadyExistsException(const char* what) : std::runtime_error(what) {}

ChannelStore::ChannelNotFoundException::ChannelNotFoundException(const char* what) : std::runtime_error(what) {}
