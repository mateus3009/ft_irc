#ifndef EVENTHANDLER_HPP
# define EVENTHANDLER_HPP

# include <poll.h>
# include "Observer.hpp"
# include "Socket.hpp"
# include "ClientStore.hpp"
# include "EventListener.hpp"

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

class NewSocketConnectionHandler : public Observer<SocketConnection>
{
    private:
        EventListener*  _eventListener;

    public:
        NewSocketConnectionHandler(void);

        NewSocketConnectionHandler(EventListener* eventListener);

        NewSocketConnectionHandler(const NewSocketConnectionHandler& other);

        ~NewSocketConnectionHandler();

        NewSocketConnectionHandler& operator=(const NewSocketConnectionHandler& other);

        void handle(SocketConnection& socket);
};

class NewSocketDisconnectionHandler : public Observer<SocketConnection>
{
    private:
        EventListener*  _eventListener;

    public:
        NewSocketDisconnectionHandler(void);

        NewSocketDisconnectionHandler(EventListener* eventListener);

        NewSocketDisconnectionHandler(const NewSocketDisconnectionHandler& other);

        ~NewSocketDisconnectionHandler();

        NewSocketDisconnectionHandler& operator=(const NewSocketDisconnectionHandler& other);

        void handle(SocketConnection& socket);
};

#endif

