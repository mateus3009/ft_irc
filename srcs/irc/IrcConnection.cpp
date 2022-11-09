#include "irc/IrcConnection.hpp"

IrcConnection::IrcConnection(ConnectionProxy& proxy) : _proxy(proxy), _client()
{
    _client = Router::_clientStore->add(_proxy.getId(), "localhost", *this);
}

void IrcConnection::send(const Message& msg) { _proxy.send(msg.toString()); }

void IrcConnection::accept(const Message& msg) { Router::route(msg, _client); }

void IrcConnection::close(void)
{
    Router::_clientStore->remove(_client);
    _proxy.close();
}
