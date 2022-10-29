#include "event_listener.hpp"

void event_listener::add(const int& fd)
{
    _fds.push_back((pollfd){.fd = fd, .events = POLLIN});
}

void event_listener::remove(const int& fd)
{
    std::vector<pollfd>::iterator it;

    it = _fds.begin();
    while (it != _fds.end())
    {
        if (it->fd == fd)
            _fds.erase(it);
        else
            ++it;
    }
}

void event_listener::listen(void)
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

void event_listener::subscribe(observer<pollfd>* observer)
{
    _publisher.subscribe(observer);
}

void event_listener::notify(const pollfd& fd)
{
    _publisher.notify(fd);
}

