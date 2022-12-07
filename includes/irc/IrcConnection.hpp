#ifndef IRCCONNECTION_HPP
# define IRCCONNECTION_HPP

# include "../network/Connection.hpp"
# include "Message.hpp"
# include "Router.hpp"

class Client;

class IrcConnection
{
    private:
        ConnectionProxy _proxy;

        shared_ptr<Client> _client;

    public:
        IrcConnection(ConnectionProxy& proxy);

        void send(const Message& msg);

        void accept(const Message& msg);

        void close(void);

        ConnectionProxy& getProxy(void);

        std::string getHostname(void) const;

        int getId(void) const;

};

#endif
