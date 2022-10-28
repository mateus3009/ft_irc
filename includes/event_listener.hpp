#ifndef event_listener_HPP
# define event_listener_HPP

# include <vector>
# include <poll.h>
# include <iostream>
# include <stdexcept>
# include <cerrno>
# include <cstring>

# include "observer.hpp"

class event_listener
{
    private:
        std::vector<pollfd> _fds;

        publisher<pollfd>   _publisher;

        void notify(const pollfd& fd);

    public:
        void add(const int& fd);

        void remove(const int& fd);

        void listen(void);

        void subscribe(observer<pollfd>* observer);

};

#endif
