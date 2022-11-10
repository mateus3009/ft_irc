#include "irc/commands/Help.hpp"

const bool Help::isRegistered = Router::add("HELP", Help::handle);

void Help::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
    ClientStore&,
    ChannelStore&,
    IrcServer&          ircServer)
{
    if (msg.params.empty())
    {
        Message response = Message() << client->getNickname() << "*";
        client->send(response << ircServer.getSource() << RPL_HELPSTART << "** Help System **");
        client->send(response << ircServer.getSource() << RPL_ENDOFHELP << "Try /HELP <command> for specific help");
        return ;
    }

    client->send(Message() << ircServer.getSource() << ERR_HELPNOTFOUND << client->getNickname() << msg.params.front() << "No help available on this topic");
}
