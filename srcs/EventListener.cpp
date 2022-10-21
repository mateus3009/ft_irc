#include "EventListener.hpp"

EventListener::EventListener(void) : _fds() {}

EventListener::EventListener(const EventListener &other) : _fds(other._fds) {}

EventListener::~EventListener() {}

EventListener &EventListener::operator=(const EventListener &other)
{
    _fds = other._fds;
    return *this;
}

void EventListener::add(const int& fd)
{
    _fds.push_back((pollfd){.fd = fd, .events = POLLIN});
}

void EventListener::remove(const int& fd)
{
    for (std::vector<pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it)
    {
        if (it->fd == fd)
            _fds.erase(it);
    }
}

void EventListener::listen(void)
{
    int events;
    std::vector<pollfd>::iterator it;

    while (true)
    {
        events = poll(_fds.data(), _fds.size(), 1200);
        if (events < 0)
            throw std::runtime_error(strerror(errno));

        for (it = _fds.begin(); it != _fds.end() && events > 0; ++it)
        {
            if (!(it->revents & POLLIN))
                continue ;

            --events;

            notify(*it);
        }
    }
}

void EventListener::subscribe(Observer<pollfd>* observer)
{
    _publisher.subscribe(observer);
}

void EventListener::notify(const pollfd& fd)
{
    _publisher.notify(fd);
}

