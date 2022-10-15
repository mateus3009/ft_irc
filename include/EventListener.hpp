#ifndef EVENTLISTENER_HPP
# define EVENTLISTENER_HPP

# include "FileDescriptor.hpp"
# include <poll.h>
# include <vector>
# include <map>

struct EventHandler : public virtual FileDescriptor
{
    virtual int handleEvent(EventListener* listener) = 0;
};

class EventListener
{
    private:
        std::vector<pollfd> fds;

        std::map<int, EventHandler*> handlers;

    public:
        EventListener(void);

        virtual ~EventListener();

        void add(EventHandler* handler);

        void remove(const int& fd);

        void listen(void);
};

#endif

