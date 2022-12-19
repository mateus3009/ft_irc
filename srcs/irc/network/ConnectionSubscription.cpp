#include "irc/network/ConnectionSubscription.hpp"

/* ConnectionSubcription */

ConnectionSubscription::ConnectionSubscription(
    FileDescriptorObserver& observer,
    ConnectionSubscriptionStore& connectionStore,
    shared_ptr<SocketConnection> connection,
    ClientStore& clientStore) :
        Subscription(observer, connection->getId()),
        _connectionStore(&connectionStore),
        _connection(connection),
        _input(connection),
        _output(connection),
        _client(),
        _isClosing(false)
{
    std::cout << "0< new connection: " << _connection->getId() << std::endl;
    _client = clientStore.add(*this);
    _client->setHostname(Socket::getHostname(_connection->getpeername()));
}

void ConnectionSubscription::handle(const short& events)
{
    Message res;
    res.source.nickname = CommandRouter::serverContext->serverName;
    res.params.push_back(_client->getNickname());
    try
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
                error(e.what());
                return ;
            }
        }

        if (events & POLLIN)
        {
            try
            {
                std::vector<std::string> msgs = _input.read();
                for (std::vector<std::string>::iterator it = msgs.begin(); it != msgs.end() && !_isClosing; ++it)
                {
                    Message msg = Message(*it);
                    CommandRouter::call(msg, _client);
                }
            }
            catch(const InputBuffer::ClosedConnectionException& e)
            {
                error(e.what());
                return ;
            }
            catch(const InputBuffer::NoSpaceLeftException& e)
            {
                std::cerr << "0< " << e.what() << std::endl;
                _client->send(res << ERR_INPUTTOOLONG << "Input line was too long");
                _input.clear();
                return ;
            }
        }

        if ((events & (POLLHUP | POLLERR | POLLNVAL) || _isClosing) && !_output.queued())
        {
            error("is closing");
        }
    }
    catch(const std::exception& e)
    {
        error(e.what());
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

void ConnectionSubscription::error(const std::string& what)
{
    std::cerr << "0< closing connection: " << _connection->getId() << " " << what << std::endl;
    _client->close();
    CommandRouter::channelStore->removeFromAllChannels(_client->getNickname());
    _connectionStore->remove(_connection->getId());
}

/* ConnectionSubcriptionStore */

ConnectionSubscriptionStore::ConnectionSubscriptionStore(
    FileDescriptorObserver& observer, ClientStore& clientStore)
        : _connections(), _observer(&observer), _clientStore(&clientStore) {}

void ConnectionSubscriptionStore::add(
    shared_ptr<SocketConnection> connection)
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
