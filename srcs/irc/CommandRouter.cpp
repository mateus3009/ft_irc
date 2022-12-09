#include "irc/CommandRouter.hpp"

std::map<std::string, CommandRegister> CommandRouter::_commands;

ClientStore* CommandRouter::clientStore;

ChannelStore* CommandRouter::channelStore;

ServerContext* CommandRouter::serverContext;

bool CommandRouter::add(
    const std::string& name, const CommandRegister& commandRegister)
{
    return CommandRouter::_commands.insert(
        std::make_pair(name, commandRegister)).second;
}

void CommandRouter::call(const Message& msg, shared_ptr<Client>& client)
{
    std::cout << client->getId() << "> " << msg << std::endl;

    std::map<std::string, CommandRegister>::iterator it =
        CommandRouter::_commands.find(msg.verb);

    if (it == CommandRouter::_commands.end())
    {
        client->send(
            Message()
                << ERR_UNKNOWNCOMMAND
                << client->getNickname()
                << msg.verb << "Unknown command");
        return ;
    }

    const CommandRegister& commandRegister = it->second;

    if (commandRegister.isRegistered && !client->isRegistered)
    {
        client->send(
            Message()
                << ERR_NOTREGISTERED
                << "You have not registered");
        return ;
    }

    if (commandRegister.paramsMin > msg.params.size())
    {
        client->send(
            Message()
                << ERR_NEEDMOREPARAMS
                << client->getNickname()
                << msg.verb
                << "Not enough parameters");
        return ;
    }

    Message res;
    res.source.nickname = serverContext->serverName;
    res.params.push_back(client->getNickname());

    Payload payload = (Payload) {
        .req = msg,
        .res = res,
        .client = client,
        .clientStore = clientStore,
        .serverContext = serverContext,
        .channelStore = channelStore};

    commandRegister.command(payload);
}
