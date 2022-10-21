#include "ClientStore.hpp"


ClientStore::ClientStore(void) : _clients() {}

ClientStore::ClientStore(const ClientStore& other) : _clients(other._clients) {}

ClientStore::~ClientStore()
{
    std::vector<SocketConnection>::iterator it;

    for (it = _clients.begin(); it != _clients.end(); ++it)
        it->close();
}

ClientStore& ClientStore::operator=(const ClientStore& other)
{
    _clients = other._clients;
    return *this;
}

void ClientStore::add(const SocketConnection& client)
{
    _clients.push_back(client);
}

void ClientStore::remove(const SocketConnection& client)
{
    std::vector<SocketConnection>::iterator it;

    for (it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->getId() != client.getId())
            continue ;
        it->close();
        _clients.erase(it);
    }
}

SocketConnection ClientStore::find(const int& fd)
{
    std::vector<SocketConnection>::iterator it;

    for (it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->getId() == fd)
            return *it;
    }
    throw std::runtime_error("Client not found!");
}

