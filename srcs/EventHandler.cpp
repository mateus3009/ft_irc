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
    std::cout << "eu cheguei aqui?" << std::endl;

    SocketConnection client;
    try
    {
        client = _clientStore->find(event.fd);
    }
    catch(const std::exception& e)
    {
        std::cout << "será que eu sai aqui?" << std::endl;
        return ;
    }

    char data[100];
    memset(data, 0, sizeof(data));

    int r = client.receive(data, sizeof(data));
    std::cout << "r: " << r << std::endl;
    if ( r <= 0)
    {
        std::cout << "removi!" << std::endl;
        _clientStore->remove(client);
        return ;
    }
    std::cout << client.getId() <<  ": " << data << std::endl;
}


