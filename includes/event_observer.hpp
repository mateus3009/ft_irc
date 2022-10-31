#ifndef EVENT_OBSERVER_HPP
# define EVENT_OBSERVER_HPP

# include <poll.h>

# include "observer.hpp"
# include "socket_server.hpp"

class event_observer : public observer<pollfd>
{
    private:
        socket_server& _store;

    public:
        event_observer(socket_server& store);

        void handle(pollfd& fd);

};

#endif
