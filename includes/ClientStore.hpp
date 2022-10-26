#ifndef CLIENTSTORE_HPP
# define CLIENTSTORE_HPP

# include "Socket.hpp"
# include "Observer.hpp"
# include <vector>
# include <algorithm>

class ClientStore
{
    private:
        std::vector<SocketConnection>   _clients;

        Publisher<SocketConnection>     _newConnection;

        Publisher<SocketConnection>     _newDisconnection;

        void notifyNewConnection(SocketConnection value);

        void notifyNewDisconnection(SocketConnection value);

    public:
        ClientStore(void);

        ClientStore(const ClientStore& other);

        ~ClientStore();

        ClientStore& operator=(const ClientStore& other);

        void add(const SocketConnection& client);

        void remove(const SocketConnection& client);

        SocketConnection find(const int& fd);

        void subscribeNewConnection(Observer<SocketConnection>* observer);

        void subscribeNewDisconnection(Observer<SocketConnection>* observer);

        std::vector<SocketConnection>::const_iterator begin(void) const;

        std::vector<SocketConnection>::const_iterator end(void) const;

};

#endif
