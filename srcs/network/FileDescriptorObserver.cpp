#include "network/FileDescriptorObserver.hpp"

/* FileDescriptorObserver */

void FileDescriptorObserver::add(
    const int& fd, const short& events, Subscription& subscription)
{
    _pollfds.push_back((pollfd){.fd = fd, .events = events, .revents = 0});
    _subscriptions.push_back(&subscription);
}

void FileDescriptorObserver::remove(const Subscription& subscription)
{
    std::vector<Subscription*>::iterator it = std::find(
        _subscriptions.begin(), _subscriptions.end(), &subscription);
    if (it != _subscriptions.end())
    {
        _pollfds.erase(_pollfds.begin() + (it - _subscriptions.begin()));
        _subscriptions.erase(it);
    }
}

void FileDescriptorObserver::update(
    const short& events, const Subscription& subscription)
{
    std::vector<Subscription*>::iterator it = std::find(
        _subscriptions.begin(), _subscriptions.end(), &subscription);
    if (it != _subscriptions.end())
        _pollfds[it - _subscriptions.begin()].events = events;
}

void FileDescriptorObserver::start(void)
{
    while (true)
    {
        int events = ::poll(_pollfds.data(), _pollfds.size(), -1);
        if (events < 0)
            throw Error();
        size_t index = 0;
        while (index < _pollfds.size() && events > 0)
        {
            const pollfd& pfd = _pollfds[index];
            if ((pfd.events | POLLHUP | POLLERR | POLLNVAL) & pfd.revents)
            {
                --events;
                _subscriptions[index]->handle(pfd.revents);
            }
            ++index;
        }
    }
}

bool operator==(const pollfd& pfd, const int& fd)
{
    return pfd.fd == fd;
}

/* Subscription */

Subscription::Subscription(
    FileDescriptorObserver& observer, const int& fd, const short& events)
    : _observer(&observer)
{
    if (fd < 0)
        throw Error("Bad file descriptor");
    _observer->add(fd, events, *this);
};

Subscription::~Subscription()
{
    _observer->remove(*this);
};

void Subscription::update(const short& events)
{
    _observer->update(events, *this);
}
