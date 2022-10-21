#ifndef CLIENTSTORE_HPP
# define CLIENTSTORE_HPP

# include "Socket.hpp"
# include <vector>
# include <algorithm>

class ClientStore
{
    private:
        std::vector<SocketConnection> _clients;

    public:
        ClientStore(void);

        ClientStore(const ClientStore& other);

        ~ClientStore();

        ClientStore& operator=(const ClientStore& other);

        void add(const SocketConnection& client);

        void remove(const SocketConnection& client);
};

#endif
