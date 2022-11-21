#include "irc/commands/commons/Welcome.hpp"

void welcome(shared_ptr<Client> client, IrcServer& ircServer)
{
    client->send(Message() << ircServer.getSource() << RPL_WELCOME << client->getNickname() << "Welcome to the " + ircServer.getServerName() + " Network, " + client->getSource().toString());
    client->send(Message() << ircServer.getSource() << RPL_YOURHOST << client->getNickname() << "Your host is " + ircServer.getServerName() + ", running version 1.0");
    client->send(Message() << ircServer.getSource() << RPL_CREATED << client->getNickname() << ":This server was created 2022-10-14");
    client->send(Message() << ircServer.getSource() << RPL_MYINFO << client->getNickname() << ircServer.getServerName() << "1.0" << "+q" << "+i");
    client->send(Message() << ircServer.getSource() << RPL_ISUPPORT << client->getNickname() << "ACCEPT=30" << "AWAYLEN=200" << "BOT=B" << "CALLERID=g" << "CASEMAPPING=ascii" << "CHANLIMIT=#:20" << "CHANMODES=IXbeg,k,Hfjl,ACKMORTcimnprstz" << "CHANNELLEN=64" << "CHANTYPES=#" << "ELIST=CMNTU" << "ESILENCE=CcdiNnPpTtx" << "EXCEPTS=e" << ":are supported by this server");
    client->send(Message() << ircServer.getSource() << RPL_ISUPPORT << client->getNickname() << "EXTBAN=,ACORTUacjrwz" << "HOSTLEN=64" << "INVEX=I" << "KEYLEN=32" << "KICKLEN=255" << "LINELEN=512" << "MAXLIST=I:100,X:100,b:100,e:100,g:100" << "MAXTARGETS=20" << "MODES=20" << "MONITOR=30" << "NAMELEN=128" << "NAMESX" << "NETWORK=Omega" << ":are supported by this server");
    client->send(Message() << ircServer.getSource() << RPL_ISUPPORT << client->getNickname() << "NICKLEN=30" << "PREFIX=(qaohv)~&@%+" << "SAFELIST" << "SILENCE=32" << "STATUSMSG=~&@%+" << "TOPICLEN=307" << "UHNAMES" << "USERIP" << "USERLEN=10" << "USERMODES=,,s,BIRcgikorw" << "WHOX" << ":are supported by this server");
}
