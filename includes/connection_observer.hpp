#ifndef CONNECTION_OBSERVER_HPP
# define CONNECTION_OBSERVER_HPP

# include <poll.h>

# include "observer.hpp"
# include "connection_handler.hpp"
# include "file_descriptor_monitor.hpp"
# include "connection.hpp"
# include "client_store.hpp"

class connection_observer : public observer<std::pair<const connection, response> >
{
    private:
        file_descriptor_monitor& _monitor;

        client_store& _store;

    public:
        connection_observer(file_descriptor_monitor& monitor, client_store& store);

        void handle(std::pair<const connection, response>& event);
};

#endif

