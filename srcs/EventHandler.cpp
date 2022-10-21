#include "EventHandler.hpp"

NewConnectionHandler::NewConnectionHandler(void) : _listener(), _clientStore() {}

NewConnectionHandler::NewConnectionHandler(const SocketListener& listener, ClientStore* clientStore) : _listener(listener), _clientStore(clientStore) {}

NewConnectionHandler::NewConnectionHandler(const NewConnectionHandler& other) : _listener(other._listener), _clientStore(other._clientStore) {}

NewConnectionHandler::~NewConnectionHandler() {}

NewConnectionHandler& NewConnectionHandler::operator=(const NewConnectionHandler& other)
{
    _listener = other._listener;
    return *this;
}

void NewConnectionHandler::handle(int fd)
{
    if (_listener.getId() != fd)
        return;

    SocketConnection client(_listener.accept());
    client.send("Hello you!\n", 12);
    _clientStore->add(client);
}
