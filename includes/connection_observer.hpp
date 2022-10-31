#ifndef CONNECTION_OBSERVER_HPP
# define CONNECTION_OBSERVER_HPP

# include <poll.h>

# include "observer.hpp"
# include "connection_handler.hpp"
# include "file_descriptor_monitor.hpp"

class connection_observer : public observer<std::pair<const int, response> >
{
    private:
        file_descriptor_monitor& _monitor;

    public:
        connection_observer(file_descriptor_monitor& monitor);

        void handle(std::pair<const int, response>& handler);
};

#endif

