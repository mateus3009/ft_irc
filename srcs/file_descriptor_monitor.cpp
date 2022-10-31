#include "file_descriptor_monitor.hpp"

void file_descriptor_monitor::add(const file_descriptor& fd)
{
    _fds.push_back((pollfd){.fd = fd.get_id(), .events = POLLIN});
}

void file_descriptor_monitor::remove(const file_descriptor& fd)
{

    std::vector<pollfd>::iterator it = std::find(_fds.begin(), _fds.end(), fd);
    if (it != _fds.end())
        _fds.erase(it);
}

void file_descriptor_monitor::listen(void)
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

void file_descriptor_monitor::subscribe(observer<pollfd>* observer)
{
    _publisher.subscribe(observer);
}

void file_descriptor_monitor::notify(const pollfd& fd)
{
    _publisher.notify(fd);
}

static bool operator==(const pollfd& pfd, const file_descriptor& fd)
{
    return pfd.fd == fd.get_id();
}
