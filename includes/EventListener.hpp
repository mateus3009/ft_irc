#ifndef EVENTLISTENER_HPP
# define EVENTLISTENER_HPP

# include <vector>
# include <poll.h>
# include <iostream>
# include <stdexcept>
# include <cerrno>
# include <cstring>

# include "Observer.hpp"

class EventListener
{
    private:
        std::vector<pollfd> _fds;

        Publisher<int>      _publisher;

        void notify(const int& fd);

    public:
        EventListener(void);

        EventListener(const EventListener& other);

        ~EventListener();

        EventListener& operator=(const EventListener& other);

        void add(const int& fd);

        void remove(const int& fd);

        void listen(void);

        void subscribe(Observer<int>* observer);

};

#endif
