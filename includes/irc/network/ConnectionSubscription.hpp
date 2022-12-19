#ifndef CONNECTIONSUBSCRIPTION_HPP
# define CONNECTIONSUBSCRIPTION_HPP

# include <map>

# include "../Client.hpp"
# include "../../network/FileDescriptorObserver.hpp"
# include "../../network/Socket.hpp"
# include "Buffer.hpp"
# include "../CommandRouter.hpp"

class ConnectionSubscriptionStore;

class Client;

class ClientStore;

class ConnectionSubscription : Subscription
{
    private:
        ConnectionSubscriptionStore* _connectionStore;

        shared_ptr<SocketConnection> _connection;

        InputBuffer _input;

        OutputBuffer _output;

        shared_ptr<Client> _client;

        bool _isClosing;

    public:
        ConnectionSubscription(
            FileDescriptorObserver& observer,
            ConnectionSubscriptionStore& connectionStore,
            shared_ptr<SocketConnection> connection,
            ClientStore& clientStore);

        virtual void handle(const short& events);

        int getId(void) const;

        void write(const std::string& str);

        void close(void);

        void error(const std::string& what);

};

class ConnectionSubscriptionStore
{
    private:
        std::map<int, shared_ptr<ConnectionSubscription> > _connections;

        FileDescriptorObserver* _observer;

        ClientStore* _clientStore;

    public:
        ConnectionSubscriptionStore(
            FileDescriptorObserver& observer, ClientStore& clientStore);

        void add(shared_ptr<SocketConnection> connection);

        void remove(const int& id);
};

#endif
