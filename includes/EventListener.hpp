#ifndef EVENTLISTENER_HPP
# define EVENTLISTENER_HPP

# include <vector>
# include <poll.h>
# include <iostream>

# include "Socket.hpp"
# include "Observer.hpp"

class EventListener
{
    private:
        std::vector<pollfd> _fds;

        Publisher<int>      _publisher;

        void notify(const int& fd);

    public:
        EventListener(void);

        EventListener(const SocketListener& listener);

        EventListener(const EventListener& other);

        ~EventListener();

        EventListener& operator=(const EventListener& other);

        void add(const int& fd);

        void remove(const int& fd);

        void listen(void);

        void subscribe(Observer<int>* observer);

};

#endif
