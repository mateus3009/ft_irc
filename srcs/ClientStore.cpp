#include "ClientStore.hpp"

ClientStore::ClientStore(void) : _clients(), _newConnection(), _newDisconnection() {}

ClientStore::ClientStore(const ClientStore& other) : _clients(other._clients), _newConnection(other._newConnection), _newDisconnection(other._newDisconnection) {}

ClientStore::~ClientStore()
{
    std::vector<SocketConnection>::iterator it;

    for (it = _clients.begin(); it != _clients.end(); ++it)
        it->close();
}

ClientStore& ClientStore::operator=(const ClientStore& other)
{
    _clients            = other._clients;
    return *this;
}

void ClientStore::add(const SocketConnection& client)
{
    _clients.push_back(client);
    _newConnection.notify(client);
}

void ClientStore::remove(const SocketConnection& client)
{
    std::vector<SocketConnection>::iterator it;

    it = _clients.begin();
    while (it != _clients.end())
    {
        if (it->getId() == client.getId())
        {
            it->close();
            _clients.erase(it);
            _newDisconnection.notify(client);
        }
        else
            ++it;
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

void ClientStore::subscribeNewConnection(Observer<SocketConnection>* observer)
{
    if (observer != NULL)
        _newConnection.subscribe(observer);
}

void ClientStore::notifyNewConnection(SocketConnection value)
{
    _newConnection.notify(value);
}

void ClientStore::subscribeNewDisconnection(Observer<SocketConnection>* observer)
{
    if (observer != NULL)
        _newDisconnection.subscribe(observer);
}

void ClientStore::notifyNewDisconnection(SocketConnection value)
{
    _newDisconnection.notify(value);
}
