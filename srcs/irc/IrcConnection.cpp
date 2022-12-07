#include "irc/IrcConnection.hpp"

IrcConnection::IrcConnection(ConnectionProxy& proxy) : _proxy(proxy), _client()
{
    _client = Router::_clientStore->add(*this);
}

void IrcConnection::send(const Message& msg) { _proxy.send(msg.toString()); }

void IrcConnection::accept(const Message& msg) { Router::route(msg, _client); }

ConnectionProxy &IrcConnection::getProxy(void){
	return _proxy;
}

void IrcConnection::close(void)
{
    Router::_clientStore->remove(_client);
    _proxy.close();
}

std::string IrcConnection::getHostname(void) const
{
    sockaddr_storage    addr;
    socklen_t           addrlen = sizeof(addr);
    ::getpeername(_proxy.getId(), (sockaddr*) &addr, &addrlen);
    char ipstr[INET6_ADDRSTRLEN];
    if (addr.ss_family == AF_INET)
        inet_ntop(addr.ss_family, &(((sockaddr_in*) &addr)->sin_addr), ipstr, INET6_ADDRSTRLEN);
    else
        inet_ntop(addr.ss_family, &(((sockaddr_in6*) &addr)->sin6_addr), ipstr, INET6_ADDRSTRLEN);
    return std::string(ipstr);
}

int IrcConnection::getId(void) const { return _proxy.getId(); }
