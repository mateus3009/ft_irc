#ifndef EVENTHANDLER_HPP
# define EVENTHANDLER_HPP

# include "Observer.hpp"
# include "Socket.hpp"
# include "ClientStore.hpp"

class NewConnectionHandler : public Observer<int>
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

        void handle(int fd);
};

#endif

