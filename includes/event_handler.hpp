#ifndef EVENTHANDLER_HPP
# define EVENTHANDLER_HPP

# include <poll.h>
# include "observer.hpp"
# include "socket_listener.hpp"
# include "client.hpp"
# include "event_listener.hpp"
# include "channel.hpp"

class new_connection_handler : public observer<pollfd>
{
    private:
        socket_listener _listener;

        client_store*   _clientStore;

    public:
        new_connection_handler(const socket_listener& listener, client_store* clientStore);

        void handle(pollfd& fd);
};

class new_data_handler : public observer<pollfd>
{
    private:
        client_store*    _clientStore;

        channel              _channel;

        void send_to_everyone(const socket_connection& client, const char* data, size_t len) const;

    public:
        new_data_handler(client_store* clientStore);

        void handle(pollfd& fd);

};

class new_socket_connection_handler : public observer<socket_connection>
{
    private:
        event_listener*  _event_listener;

    public:
        new_socket_connection_handler(event_listener* event_listener);

        void handle(socket_connection& socket);
};

class new_socket_disconnection_handler : public observer<socket_connection>
{
    private:
        event_listener*  _event_listener;

    public:
        new_socket_disconnection_handler(event_listener* event_listener);

        void handle(socket_connection& socket);
};

#endif

