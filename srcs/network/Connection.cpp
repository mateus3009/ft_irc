#include "network/Connection.hpp"

ConnectionProxy::ConnectionProxy(SocketConnection& connection, OutputBuffer& output, bool& closing) : _connection(connection), _outputBuffer(output), _closing(closing) {}

void ConnectionProxy::send(const std::string& str)
{
    if (_closing == false)
        _outputBuffer.write(str);
}

void ConnectionProxy::close(void) { _closing = true; }

int ConnectionProxy::getId(void) const { return _connection.getId(); }
