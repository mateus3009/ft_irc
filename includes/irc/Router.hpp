#ifndef ROUTER_HPP
# define ROUTER_HPP

# include <map>

# include "Client.hpp"
# include "Channel.hpp"
# include "commands/NumericReply.hpp"

class Client;
class ClientStore;
class ChannelStore;

class Router
{
    public:
        typedef void (*Command)(
            const Message&      msg,
            shared_ptr<Client>& client,
            ClientStore&        clientStore,
            ChannelStore&       channelStore);
    public:
        static ClientStore* _clientStore;

        static ChannelStore* _channelStore;

        static std::map<std::string, Command> _commands;

        static Command _notFound;

    public:
        static void route(const Message& msg, shared_ptr<Client> client);

        static void setClientStore(ClientStore* clientStore);

        static void setChannelStore(ChannelStore* channelStore);

        static void setNotFound(Command c);

        static bool add(const std::string& name, Command c);

};

#endif
