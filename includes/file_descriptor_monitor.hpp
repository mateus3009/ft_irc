#ifndef FILE_DESCRIPTOR_MONITOR
# define FILE_DESCRIPTOR_MONITOR

# include <vector>
# include <poll.h>
# include <iostream>
# include <stdexcept>
# include <cerrno>
# include <cstring>

# include "observer.hpp"
# include "file_descriptor.hpp"

class file_descriptor_monitor
{
    private:
        std::vector<pollfd> _fds;

        publisher<pollfd>   _publisher;

        void notify(const pollfd& fd);

    public:
        void add(const file_descriptor& fd);

        void remove(const file_descriptor& fd);

        void listen(void);

        void subscribe(observer<pollfd>* observer);

};

#endif
