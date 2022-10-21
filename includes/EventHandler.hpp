#ifndef EVENTHANDLER_HPP
# define EVENTHANDLER_HPP

# include <poll.h>
# include "Observer.hpp"
# include "Socket.hpp"
# include "ClientStore.hpp"

class NewConnectionHandler : public Observer<pollfd>
{
    private:
        SocketListener  _listener;

        ClientStore*    _clientStore;

    public:
        NewConnectionHandler(void);

        NewConnectionHandler(const SocketListener& listener, ClientStore* clientStore);

        NewConnectionHandler(const NewConnectionHandler& other);

        ~NewConnectionHandler();

        NewConnectionHandler& operator=(const NewConnectionHandler& other);

        void handle(pollfd& fd);
};

class NewDataHandler : public Observer<pollfd>
{
    private:
        ClientStore*    _clientStore;

    public:
        NewDataHandler(void);

        NewDataHandler(ClientStore* clientStore);

        NewDataHandler(const NewDataHandler& other);

        ~NewDataHandler();

        NewDataHandler& operator=(const NewDataHandler& other);

        void handle(pollfd& fd);
};

#endif

