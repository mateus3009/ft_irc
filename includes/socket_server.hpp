#ifndef SOCKET_SERVER_HPP
# define SOCKET_SERVER_HPP

# include <vector>
# include <poll.h>
# include <algorithm>
# include <utility>

# include "socket_listener.hpp"
# include "connection_handler.hpp"
# include "request.hpp"
# include "response.hpp"
# include "observer.hpp"

class socket_server
{
    private:
        socket_listener&                            _listener;

        std::vector<connection_handler>             _connections;

        publisher<std::pair<const int, response> >  _connection_subscribers;

        publisher<std::pair<request, response> >    _message_subscribers;

        publisher<const int>                        _disconnection_subscribers;

    public:
        socket_server(socket_listener& listener);

        void handle(pollfd& event);

        void subscribe_to_connection(observer<std::pair<const int, response> >* observer);

        void subscribe_to_message(observer<std::pair<request, response> >* observer);

        void subscribe_to_disconnection(observer<const int>* observer);

};

#endif
