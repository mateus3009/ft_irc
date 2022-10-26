#ifndef CLIENTSTORE_HPP
# define CLIENTSTORE_HPP

# include "Socket.hpp"
# include "Observer.hpp"
# include <vector>
# include <algorithm>

class GlobalClientStore
{
    private:
        std::vector<SocketConnection>   _clients;

        Publisher<SocketConnection>     _newConnection;

        Publisher<SocketConnection>     _newDisconnection;

        void notifyNewConnection(SocketConnection value);

        void notifyNewDisconnection(SocketConnection value);

    public:
        GlobalClientStore(void);

        GlobalClientStore(const GlobalClientStore& other);

        ~GlobalClientStore();

        GlobalClientStore& operator=(const GlobalClientStore& other);

        void add(const SocketConnection& client);

        void remove(const SocketConnection& client);

        SocketConnection find(const int& fd);

        void subscribeNewConnection(Observer<SocketConnection>* observer);

        void subscribeNewDisconnection(Observer<SocketConnection>* observer);

        std::vector<SocketConnection>::const_iterator begin(void) const;

        std::vector<SocketConnection>::const_iterator end(void) const;

};

#endif
