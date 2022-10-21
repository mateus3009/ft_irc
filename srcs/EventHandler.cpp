#include "EventHandler.hpp"

NewConnectionHandler::NewConnectionHandler(void) : _listener() {}

NewConnectionHandler::NewConnectionHandler(const SocketListener& listener) : _listener(listener) {}

NewConnectionHandler::NewConnectionHandler(const NewConnectionHandler& other) : _listener(other._listener) {}

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

    SocketConnection con(_listener.accept());
    con.send("hello you!", 11);
    con.close();
}
