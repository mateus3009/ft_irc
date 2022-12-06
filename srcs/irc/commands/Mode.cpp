#include "irc/commands/Mode.hpp"

const bool Mode::isRegistered = Router::add("MODE", Mode::handle);

const ModeParse* Mode::userModes = (ModeParse[]){
    (ModeParse){.id = MODE_USER_INVISIBLE,          .symbol = 'i'},
    (ModeParse){.id = MODE_USER_OPER,               .symbol = 'o'},
    (ModeParse){.id = MODE_USER_LOCAL_OPER,         .symbol = 'O'},
    (ModeParse){.id = MODE_USER_REGISTERED,         .symbol = 'r'},
    (ModeParse){.id = MODE_USER_WALLOPS,            .symbol = 'w'}};

const ModeParse* Mode::channelModes = (ModeParse[]){
    (ModeParse){.id = MODE_CHANNEL_BAN,                   .symbol = 'b'},
    (ModeParse){.id = MODE_CHANNEL_EXCEPTION,             .symbol = 'e'},
    (ModeParse){.id = MODE_CHANNEL_CLIENT_LIMIT,          .symbol = 'l'},
    (ModeParse){.id = MODE_CHANNEL_INVITE_ONLY,           .symbol = 'i'},
    (ModeParse){.id = MODE_CHANNEL_INVITE_EXCEPTION,      .symbol = 'I'},
    (ModeParse){.id = MODE_CHANNEL_KEY_CHANNEL,           .symbol = 'k'},
    (ModeParse){.id = MODE_CHANNEL_SECRET,                .symbol = 's'},
    (ModeParse){.id = MODE_CHANNEL_PROTECTED_TOPIC,       .symbol = 't'},
    (ModeParse){.id = MODE_CHANNEL_NO_EXTERNAL_MESSAGES,  .symbol = 'n'}};

void Mode::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
    ClientStore&,
    ChannelStore& channelStore,
    IrcServer& ircServer)
{
	std::cout << "MODE sendo chamado com cliente: " << client->getIdClient() << " with command: " << ((msg.params.empty()) ? "nothing" : msg.params.front()) << std::endl;

    if (!ircServer.isRegistered(client))
    {
        client->send(Message() << ircServer.getSource() << ERR_NOTREGISTERED << "You have not registered");
        return ;
    }

    if (msg.params.empty() || msg.params.front() == client->getNickname())
    {
        if (msg.params.size() == 2 && msg.params.at(1) == "+i")
            client->setModes(MODE_USER_INVISIBLE);
        else if (msg.params.size() == 2 && msg.params.at(1) == "-i")
            client->unsetModes(MODE_USER_INVISIBLE);
        else if (msg.params.size() >= 2)
        {
            client->send(Message() << ircServer.getSource() << ERR_UMODEUNKNOWNFLAG << client->getNickname() << "Unknown MODE flag");
            return ;
        }

        client->send(Message() << ircServer.getSource() << RPL_UMODEIS << client->getNickname() << toString(client->getModes(), userModes, USERMODES_SIZE));
        return ;
    }

    const std::string& target = msg.params.front();

    if (*target.c_str() == '#' || *target.c_str() == '&')
    {
        shared_ptr<Channel> channel;
        try
        {
            channel = channelStore.find(target);
        }
        catch(const ChannelStore::ChannelNotFoundException&)
        {
            client->send(Message() << ircServer.getSource() << ERR_NOSUCHCHANNEL << client->getNickname() << target << "No such channel");
            return ;
        }

        if (msg.params.size() == 1)
        {
            client->send(Message() << ircServer.getSource() << RPL_CHANNELMODEIS << client->getNickname() << target << toString(channel->getModes(), channelModes, CHANNELMODES_SIZE));
            return ;
        }

        client->send(Message() << ircServer.getSource() << ERR_CHANOPRIVSNEEDED  << client->getNickname() << target << "Cant change mode for this channel");
        return ;
    }

    if (msg.params.size() >= 1)
    {
        client->send(Message() << ircServer.getSource() << ERR_USERSDONTMATCH << client->getNickname() << "Cant see or change mode for other users");
        return ;
    }

    client->send(Message() << ircServer.getSource() << ERR_UNKNOWNERROR << client->getNickname() << msg.verb << "Cant see or change mode");
}

std::string Mode::toString(unsigned int modes, const ModeParse* collection, size_t len)
{
    std::stringstream stream;

    for (size_t index = 0; index != len; ++index)
    {
        if (modes & collection[index].id)
            stream << collection[index].symbol;
    }
    return stream.str();
}
