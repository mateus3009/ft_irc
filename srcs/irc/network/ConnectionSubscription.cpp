#include "irc/network/ConnectionSubscription.hpp"

/* ConnectionSubcription */

ConnectionSubscription::ConnectionSubscription(
    FileDescriptorObserver& observer,
    ConnectionSubscriptionStore& connectionStore,
    const shared_ptr<SocketConnection>& connection,
    ClientStore& clientStore) :
        Subscription(observer, connection->getId()),
        _connectionStore(&connectionStore),
        _connection(connection),
        _input(connection),
        _output(connection),
        _isClosing(false)
{
    _client = clientStore.add(*this);
    _client->setHostname(Socket::getHostname(_connection->getpeername()));
}

void ConnectionSubscription::handle(const short& events)
{
    if (events & POLLOUT)
    {
        try
        {
            _output.flush();
            if (!_output.queued())
                update(POLLIN);
        }
        catch(const Error& e)
        {
            std::cerr << e.what() << '\n';
            _client->close();
            _connectionStore->remove(_connection->getId());
            return ;
        }
    }

    if (events & POLLIN)
    {
        try
        {
            std::vector<std::string> msgs = _input.read();
            for (std::vector<std::string>::iterator it = msgs.begin(); it != msgs.end(); ++it)
            {
                Message msg = Message(*it);
                CommandRouter::call(msg, _client);
            }
        }
        catch(const InputBuffer::ClosedConnectionException& e)
        {
            std::cerr << e.what() << '\n';
            _client->close();
            _connectionStore->remove(_connection->getId());
            return ;
        }
    }

    if ((events & (POLLHUP | POLLERR | POLLNVAL) || _isClosing) && !_output.queued())
    {
        _client->close();
        _connectionStore->remove(_connection->getId());
    }
}

int ConnectionSubscription::getId(void) const { return _connection->getId(); }

void ConnectionSubscription::write(const std::string& str)
{
    if (!_isClosing)
    {
        update(POLLIN | POLLOUT);
        _output.write(str);
    }
}

void ConnectionSubscription::close(void) { _isClosing = true; }

/* ConnectionSubcriptionStore */

ConnectionSubscriptionStore::ConnectionSubscriptionStore(
    FileDescriptorObserver& observer, ClientStore& clientStore)
        : _observer(&observer), _clientStore(&clientStore) {}

void ConnectionSubscriptionStore::add(
    const shared_ptr<SocketConnection>& connection)
{
    shared_ptr<ConnectionSubscription> sub =
        shared_ptr<ConnectionSubscription>::make_shared(
            new ConnectionSubscription(*_observer, *this, connection, *_clientStore));
    _connections.insert(std::make_pair(connection->getId(), sub));
}

void ConnectionSubscriptionStore::remove(const int& id)
{
    _connections.erase(id);
}