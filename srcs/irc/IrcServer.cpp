#include "irc/IrcServer.hpp"

IrcServer::IrcServer(void) : _motd(), _password(), _serverName() {}

std::string IrcServer::getMotd(void) const { return _motd; }

void IrcServer::setMotd(const std::string& motd) { _motd = motd; }

std::string IrcServer::getPassword(void) const { return _password; }

void IrcServer::setPassword(const std::string& password) { _password = password; }

std::string IrcServer::getServerName(void) const { return _serverName; }

void IrcServer::setServerName(const std::string& serverName) { _serverName = serverName; }

std::string IrcServer::getWelcomeMessage(void) const { return _welcomeMessage; }

void IrcServer::setWelcomeMessage(const std::string& welcomeMessage) { _welcomeMessage = welcomeMessage; }

Message::Source IrcServer::getSource(void) const
{
    return (Message::Source) { .nickname = _serverName };
}
