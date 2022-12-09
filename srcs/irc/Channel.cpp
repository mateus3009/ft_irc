#include "irc/Channel.hpp"

/* Membership */

Membership::Membership(shared_ptr<Client> client)
    : _client(client), _isFounder(false), _isModerator(false) {}

shared_ptr<Client> Membership::getClient(void) const { return _client; }

bool Membership::isFounder(void) const { return _isFounder; }

bool Membership::isModerator(void) const { return _isModerator; }

bool operator==(const Membership& l, const Membership& r)
{
    return strcasecmp(
        l.getClient()->getNickname().c_str(),
        r.getClient()->getNickname().c_str()) == 0;
}

bool operator<(const Membership& l, const Membership& r)
{
    return strcasecmp(
        l.getClient()->getNickname().c_str(),
        r.getClient()->getNickname().c_str()) < 0;
}

static bool validChannelCharacter(unsigned char c)
{
    return ::isalnum(c) || c == '-' || c == '_';
}

/* Channel */

Channel::Channel(
    const std::string& name, shared_ptr<Client> founder, ChannelStore& store)
    : _name(name), _store(&store)
{
    if (name.size() < 6
        || 21 < name.size()
        || !allOf(name.begin() + 1, name.end(), validChannelCharacter)
        || strchr("#&", *name.begin()) == NULL)
        throw InvalidChannelNameException(
            "The channel name must match the expression [#&][a-zA-Z]{5,20}");
    shared_ptr<Membership> membership = add(founder);
    membership->_isFounder = true;
}

std::string Channel::getName(void) const { return _name; }

std::string Channel::getTopic(void) const { return _topic; }

void Channel::setTopic(const std::string& topic) { _topic = topic; }

std::string Channel::getKey(void) const { return _key; }

void Channel::setKey(const std::string& key) { _key = key; }

shared_ptr<Membership> Channel::add(shared_ptr<Client> client)
{
    std::set<shared_ptr<Membership> >::iterator it =
        std::find(_memberships.begin(), _memberships.end(), client);
    if (it != _memberships.end())
        throw Channel::ClientIsAlreadyAMemberException(
            "The Client is already a member of this channel!");
    shared_ptr<Membership> membership =
        shared_ptr<Membership>::make_shared(new Membership(client));
    _memberships.insert(membership);
    return membership;
}

shared_ptr<Membership> Channel::find(shared_ptr<Client> client)
{
    std::set<shared_ptr<Membership> >::iterator it =
        std::find(_memberships.begin(), _memberships.end(), client);
    if (it == _memberships.end())
        throw Channel::ClientNotFoundException(
            "The client is not a member of this channel!");
    return *it;
}

void Channel::remove(shared_ptr<Membership>& membership)
{
    std::set<shared_ptr<Membership> >::iterator it =
        _memberships.find(membership);
    if (it == _memberships.end())
        throw Channel::ClientNotFoundException(
            "The client is not a member of this channel!");

    _memberships.erase(membership);

    if (_memberships.empty())
        _store->remove(_name);
}

void Channel::broadcast(const Message& msg)
{
    std::set<shared_ptr<Membership> >::iterator it = _memberships.begin();
    while (it != _memberships.end())
    {
        (*it)->getClient()->send(msg);
        ++it;
    }
}

std::set<shared_ptr<Membership> >::iterator Channel::begin(void) const
{
    return _memberships.begin();
}

std::set<shared_ptr<Membership> >::iterator Channel::end(void) const
{
    return _memberships.end();
}

Channel::InvalidChannelNameException::InvalidChannelNameException(
    const char* what) : Error(what) {}

Channel::ClientIsAlreadyAMemberException::ClientIsAlreadyAMemberException(
    const char* what) : Error(what) {}

Channel::ClientNotFoundException::ClientNotFoundException(const char* what)
    : Error(what) {}


bool operator==(const Channel& channel, const std::string& name)
{
    if (name.empty())
        return false;
    return strcasecmp(channel.getName().c_str() + 1, name.c_str() + 1) == 0;
}

bool operator==(const Channel& l, const Channel& r)
{
    return strcasecmp(l.getName().c_str() + 1, r.getName().c_str() + 1) == 0;
}

bool operator<(const Channel& l, const Channel& r)
{
    return strcasecmp(l.getName().c_str() + 1, r.getName().c_str() + 1);
}

/* ChannelStore */

shared_ptr<Channel> ChannelStore::add(shared_ptr<Client> client, const std::string& name)
{
    std::set<shared_ptr<Channel> >::iterator it =
        std::find(_channels.begin(), _channels.end(), name);
    if (it != _channels.end())
        throw ChannelStore::ChannelAlreadyExistsException(
            "Two channels cannot have the same name!");
    shared_ptr<Channel> channel =
        shared_ptr<Channel>::make_shared(new Channel(name, client, *this));
    _channels.insert(channel);
    return channel;
}

shared_ptr<Channel> ChannelStore::find(const std::string& name)
{
    std::set<shared_ptr<Channel> >::iterator it =
        std::find(_channels.begin(), _channels.end(), name);
    if (it == _channels.end())
        throw ChannelStore::ChannelNotFoundException(
            "There is no channel with this name!");
    return *it;
}

void ChannelStore::remove(const std::string& name)
{
    std::set<shared_ptr<Channel> >::iterator it =
        std::find(_channels.begin(), _channels.end(), name);
    if (it != _channels.end())
        _channels.erase(it);
}

ChannelStore::ChannelAlreadyExistsException::ChannelAlreadyExistsException(
    const char* what) : Error(what) {}

ChannelStore::ChannelNotFoundException::ChannelNotFoundException(
    const char* what) : Error(what) {}
