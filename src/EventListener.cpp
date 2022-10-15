#include "EventListener.hpp"


EventListener::EventListener(void) : fds(), handlers() {}

EventListener::~EventListener() {}

void EventListener::add(EventHandler* handler)
{
    if (handlers.find(handler->getId()) == handlers.end())
        throw std::runtime_error("Handler already exists!");

    handlers.insert(std::make_pair(handler->getId(), handler));
    fds.push_back((pollfd) { .fd = handler->getId(), .events = POLLIN });
}

void EventListener::remove(const int& fd)
{
    if (handlers.find(fd) == handlers.end())
        throw std::runtime_error("Handler does not exists");

    handlers.erase(fd);
    for (std::vector<pollfd>::const_iterator
        it = fds.begin(), end = fds.end();
        it != end; ++it)
    {
        if (it->fd != fd)
            continue ;
        fds.erase(it);
        break ;
    }
}

void EventListener::listen(void)
{
    int events;

    while (true)
    {
        events = poll(fds.data(), fds.size(), 10000);
        if (events < 0)
            throw std::runtime_error(strerror(errno));

        for (std::vector<pollfd>::const_iterator it = fds.begin();
            it != fds.end() && events > 0; ++it)
        {
            if (!(it->revents & POLLIN))
                continue ;

            --events;

            if (handlers[it->fd]->handleEvent(this) < 0)
                this->remove(it->fd);
        }
    }
}
