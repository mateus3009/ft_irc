#include "irc/Router.hpp"

ClientStore*    Router::_clientStore;

ChannelStore*   Router::_channelStore;

IrcServer*      Router::_ircServer;

std::map<std::string, Router::Command> Router::_commands;

Router::Command Router::_notFound;

void Router::route(const Message& msg, shared_ptr<Client> client)
{
    std::map<std::string, Command>::iterator it = _commands.find(msg.verb);
    if (it != _commands.end())
        it->second(msg, client, *_clientStore, *_channelStore, *_ircServer);
    else
        _notFound(msg, client, *_clientStore, *_channelStore, *_ircServer);
}

void Router::setClientStore(ClientStore* clientStore) { _clientStore = clientStore; }

void Router::setChannelStore(ChannelStore* channelStore) { _channelStore = channelStore; }

void Router::setIrcServer(IrcServer* ircServer) { _ircServer = ircServer; }

void Router::setNotFound(Command c) { _notFound = c; }

bool Router::add(const std::string& name, Command c) { return Router::_commands.insert(std::make_pair(name, c)).second; }
