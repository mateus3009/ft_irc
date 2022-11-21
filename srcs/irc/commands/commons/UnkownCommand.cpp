#include "irc/commands/commons/UnkownCommand.hpp"

const bool UnkownCommand::isRegistered = false;

void UnkownCommand::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
    ClientStore&,
    ChannelStore&,
    IrcServer&  ircServer)
{
    client->send(Message() << ircServer.getSource() << ERR_UNKNOWNCOMMAND << client->getNickname() << msg.verb << "Unknown command");
}
