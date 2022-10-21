#ifndef EVENTHANDLER_HPP
# define EVENTHANDLER_HPP

# include "Observer.hpp"
# include "Socket.hpp"

class NewConnectionHandler : public Observer<int>
{
    private:
        SocketListener _listener;

    public:
        NewConnectionHandler(void);

        NewConnectionHandler(const SocketListener& listener);

        NewConnectionHandler(const NewConnectionHandler& other);

        ~NewConnectionHandler();

        NewConnectionHandler& operator=(const NewConnectionHandler& other);

        void handle(int fd);
};

#endif

