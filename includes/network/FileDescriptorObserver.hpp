#ifndef FILEDESCRIPTOROBSERVER_HPP
# define FILEDESCRIPTOROBSERVER_HPP

# include <poll.h>
# include <vector>
# include <algorithm>

# include "../utils/Error.hpp"

class FileDescriptorObserver;

class Subscription
{
    protected:
        FileDescriptorObserver* _observer;

    public:
        Subscription(
            FileDescriptorObserver& observer,
            const int& fd,
            const short& events = POLLIN);

        virtual ~Subscription();

        virtual void handle(const short& events) = 0;

        void update(const short& events);

};

bool operator==(const pollfd& pfd, const int& fd);

class FileDescriptorObserver
{
    private:
        std::vector<pollfd> _pollfds;

        std::vector<Subscription*> _subscriptions;

    protected:
        void add(const int& fd, const short& events, Subscription& subscription);

        void remove(const Subscription& subscription);

        void update(const short& events, const Subscription& subscription);

    public:
        void start(void);

    friend class Subscription;

};

#endif
