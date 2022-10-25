#include "EventHandler.hpp"

NewConnectionHandler::NewConnectionHandler(void) : _listener(), _clientStore() {}

NewConnectionHandler::NewConnectionHandler(const SocketListener& listener, ClientStore* clientStore) : _listener(listener), _clientStore(clientStore) {}

NewConnectionHandler::NewConnectionHandler(const NewConnectionHandler& other) : _listener(other._listener), _clientStore(other._clientStore) {}

NewConnectionHandler::~NewConnectionHandler() {}

NewConnectionHandler& NewConnectionHandler::operator=(const NewConnectionHandler& other)
{
    _listener       = other._listener;
    _clientStore    = other._clientStore;
    return *this;
}

void NewConnectionHandler::handle(pollfd& event)
{
    if (_listener.getId() != event.fd)
        return;

    SocketConnection client(_listener.accept());
    client.send("Hello you!\n", 12);
    _clientStore->add(client);
}

NewDataHandler::NewDataHandler(void) : _clientStore() {}

NewDataHandler::NewDataHandler(ClientStore* clientStore) : _clientStore(clientStore) {}

NewDataHandler::NewDataHandler(const NewDataHandler& other) : _clientStore(other._clientStore) {}

NewDataHandler::~NewDataHandler() {}

NewDataHandler& NewDataHandler::operator=(const NewDataHandler& other)
{
    _clientStore    = other._clientStore;
    return *this;
}

void NewDataHandler::handle(pollfd& event)
{
    SocketConnection client;
    try
    {
        client = _clientStore->find(event.fd);
    }
    catch(const std::exception& e)
    {
        return ;
    }

    char data[100];
    memset(data, 0, sizeof(data));

    int r = client.receive(data, sizeof(data));
    if ( r <= 0)
    {
        _clientStore->remove(client);
        return ;
    }

    std::vector<SocketConnection>::const_iterator it = _clientStore->begin();
    while (it != _clientStore->end())
    {
        try
        {
            it->send(data, r);
            ++it;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error when sending data to " << it->getId() << std::endl;
            _clientStore->remove(*it);
        }
    }
}

NewSocketConnectionHandler::NewSocketConnectionHandler(void) : _eventListener() {}

NewSocketConnectionHandler::NewSocketConnectionHandler(EventListener* eventListener) : _eventListener(eventListener) {}

NewSocketConnectionHandler::NewSocketConnectionHandler(const NewSocketConnectionHandler& other)  : _eventListener(other._eventListener) {}

NewSocketConnectionHandler::~NewSocketConnectionHandler() {}

NewSocketConnectionHandler& NewSocketConnectionHandler::operator=(const NewSocketConnectionHandler& other)
{
    _eventListener = other._eventListener;
    return *this;
}

void NewSocketConnectionHandler::handle(SocketConnection& socket)
{
    _eventListener->add(socket.getId());
}

NewSocketDisconnectionHandler::NewSocketDisconnectionHandler(void) : _eventListener() {}

NewSocketDisconnectionHandler::NewSocketDisconnectionHandler(EventListener* eventListener) : _eventListener(eventListener) {}

NewSocketDisconnectionHandler::NewSocketDisconnectionHandler(const NewSocketDisconnectionHandler& other)  : _eventListener(other._eventListener) {}

NewSocketDisconnectionHandler::~NewSocketDisconnectionHandler() {}

NewSocketDisconnectionHandler& NewSocketDisconnectionHandler::operator=(const NewSocketDisconnectionHandler& other)
{
    _eventListener = other._eventListener;
    return *this;
}

void NewSocketDisconnectionHandler::handle(SocketConnection& socket)
{
    std::cout << socket.getId() << " is leaving us! :(" << std::endl;
    _eventListener->remove(socket.getId());
}
