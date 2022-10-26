#include "ClientStore.hpp"

GlobalClientStore::GlobalClientStore(void) : _clients(), _newConnection(), _newDisconnection() {}

GlobalClientStore::GlobalClientStore(const GlobalClientStore& other) : _clients(other._clients), _newConnection(other._newConnection), _newDisconnection(other._newDisconnection) {}

GlobalClientStore::~GlobalClientStore()
{
    std::vector<SocketConnection>::iterator it;

    for (it = _clients.begin(); it != _clients.end(); ++it)
        it->close();
}

GlobalClientStore& GlobalClientStore::operator=(const GlobalClientStore& other)
{
    _clients            = other._clients;
    return *this;
}

void GlobalClientStore::add(const SocketConnection& client)
{
    _clients.push_back(client);
    _newConnection.notify(client);
}

void GlobalClientStore::remove(const SocketConnection& client)
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

SocketConnection GlobalClientStore::find(const int& fd)
{
    std::vector<SocketConnection>::iterator it;

    for (it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->getId() == fd)
            return *it;
    }
    throw std::runtime_error("Client not found!");
}

void GlobalClientStore::subscribeNewConnection(Observer<SocketConnection>* observer)
{
    if (observer != NULL)
        _newConnection.subscribe(observer);
}

void GlobalClientStore::notifyNewConnection(SocketConnection value)
{
    _newConnection.notify(value);
}

void GlobalClientStore::subscribeNewDisconnection(Observer<SocketConnection>* observer)
{
    if (observer != NULL)
        _newDisconnection.subscribe(observer);
}

void GlobalClientStore::notifyNewDisconnection(SocketConnection value)
{
    _newDisconnection.notify(value);
}

std::vector<SocketConnection>::const_iterator GlobalClientStore::begin(void) const
{
    return _clients.begin();
}

std::vector<SocketConnection>::const_iterator GlobalClientStore::end(void) const
{
    return _clients.end();
}
