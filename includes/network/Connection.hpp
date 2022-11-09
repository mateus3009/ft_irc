#ifndef CONNECTION_HPP
# define CONNECTION_HPP

# include "Socket.hpp"

# include "Socket.hpp"
# include "Buffer.hpp"

class ConnectionProxy
{
    private:
        SocketConnection&    _connection;

        OutputBuffer&       _outputBuffer;

        bool&               _closing;

    public:
        ConnectionProxy(SocketConnection& connection, OutputBuffer& output, bool& closing);

        void send(const std::string& str);

        void close(void);

        int getId(void) const;
};

template <typename T>
class Connection
{
    private:
        SocketConnection    _connection;

        InputBuffer         _inputBuffer;

        OutputBuffer        _outputBuffer;

        bool                _closing;

        ConnectionProxy     _proxy;

        T                   _handler;

    public:
        Connection(const SocketConnection& connection) :
            _connection(connection),
            _inputBuffer(connection),
            _outputBuffer(connection),
            _closing(false),
            _proxy(_connection, _outputBuffer, _closing),
            _handler(T(_proxy)) {}

        void receive(void)
        {
            const std::vector<std::string> msgs = _inputBuffer.read();
            for (std::vector<std::string>::const_iterator it = msgs.begin(); it != msgs.end(); ++it)
                _handler.accept(*it);
        }

        void send(void) { _outputBuffer.flush(); }

        bool isClosing(void) const { return _closing; }

        void close(void) { _connection.close(); }

        int getId(void) const { return _connection.getId(); }

        bool isQueued(void) const { return _outputBuffer.queued(); }

};

#endif
