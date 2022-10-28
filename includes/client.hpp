#ifndef CLIENTSTORE_HPP
# define CLIENTSTORE_HPP

# include "socket_connection.hpp"
# include "observer.hpp"
# include <vector>
# include <algorithm>

class client_store
{
    private:
        std::vector<socket_connection>  _clients;

        publisher<socket_connection>    _newConnection;

        publisher<socket_connection>    _newDisconnection;

        void notify_new_connection(socket_connection value);

        void notify_new_disconnection(socket_connection value);

    public:
        client_store(void);

        client_store(const client_store& other);

        ~client_store();

        client_store& operator=(const client_store& other);

        void add(const socket_connection& client);

        void remove(const socket_connection& client);

        socket_connection find(const int& fd);

        void subscribe_new_connection(observer<socket_connection>* observer);

        void subscribe_new_disconnection(observer<socket_connection>* observer);

        std::vector<socket_connection>::const_iterator begin(void) const;

        std::vector<socket_connection>::const_iterator end(void) const;

};

#endif
