#ifndef COMMANDROUTER_HPP
# define COMMANDROUTER_HPP

# include <map>

# include "Message.hpp"
# include "Client.hpp"
# include "Server.hpp"
# include "NumericReply.hpp"
# include "Channel.hpp"

class Client;

class ClientStore;

class Channel;

class ChannelStore;

struct ServerContext;

struct Payload
{
    Message req;

    Message res;

    shared_ptr<Client>& client;

    ClientStore* clientStore;

    ServerContext* serverContext;

    ChannelStore* channelStore;

};

typedef void (*Command)(Payload&);

struct CommandRegister
{
    Command command;

    bool isRegistered;

    unsigned long paramsMin;

};

class CommandRouter
{
    public:
        static std::map<std::string, CommandRegister> _commands;

        static ClientStore* clientStore;

        static ChannelStore* channelStore;

        static ServerContext* serverContext;

        static bool add(const std::string& name, const CommandRegister& commandRegister);

        static void call(const Message& msg, shared_ptr<Client>& client);

};

#endif
