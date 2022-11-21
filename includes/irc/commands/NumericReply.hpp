#ifndef NUMERICREPLY_HPP
# define NUMERICREPLY_HPP

# define RPL_WELCOME            Verb("001")
# define RPL_YOURHOST           Verb("002")
# define RPL_CREATED            Verb("003")
# define RPL_MYINFO             Verb("004")
# define RPL_ISUPPORT           Verb("005")
# define RPL_BOUNCE             Verb("010")
# define RPL_UMODEIS            Verb("221")
# define RPL_LUSERCLIENT        Verb("251")
# define RPL_LUSEROP            Verb("252")
# define RPL_LUSERUNKNOWN       Verb("253")
# define RPL_LUSERCHANNELS      Verb("254")
# define RPL_LUSERME            Verb("255")
# define RPL_ADMINME            Verb("256")
# define RPL_ADMINLOC1          Verb("257")
# define RPL_ADMINLOC2          Verb("258")
# define RPL_ADMINEMAIL         Verb("259")
# define RPL_TRYAGAIN           Verb("263")
# define RPL_LOCALUSERS         Verb("265")
# define RPL_GLOBALUSERS        Verb("266")
# define RPL_WHOISCERTFP        Verb("276")
# define RPL_NONE               Verb("300")
# define RPL_AWAY               Verb("301")
# define RPL_USERHOST           Verb("302")
# define RPL_UNAWAY             Verb("305")
# define RPL_NOWAWAY            Verb("306")
# define RPL_WHOREPLY           Verb("352")
# define RPL_ENDOFWHO           Verb("315")
# define RPL_WHOISREGNICK       Verb("307")
# define RPL_WHOISUSER          Verb("311")
# define RPL_WHOISSERVER        Verb("312")
# define RPL_WHOISOPERATOR      Verb("313")
# define RPL_WHOWASUSER         Verb("314")
# define RPL_WHOISIDLE          Verb("317")
# define RPL_ENDOFWHOIS         Verb("318")
# define RPL_WHOISCHANNELS      Verb("319")
# define RPL_WHOISSPECIAL       Verb("320")
# define RPL_LISTSTART          Verb("321")
# define RPL_LIST               Verb("322")
# define RPL_LISTEND            Verb("323")
# define RPL_CHANNELMODEIS      Verb("324")
# define RPL_CREATIONTIME       Verb("329")
# define RPL_WHOISACCOUNT       Verb("330")
# define RPL_NOTOPIC            Verb("331")
# define RPL_TOPIC              Verb("332")
# define RPL_TOPICWHOTIME       Verb("333")
# define RPL_INVITELIST         Verb("336")
# define RPL_ENDOFINVITELIST    Verb("337")
# define RPL_WHOISACTUALLY      Verb("338")
# define RPL_INVITING           Verb("341")
# define RPL_INVEXLIST          Verb("346")
# define RPL_ENDOFINVEXLIST     Verb("347")
# define RPL_EXCEPTLIST         Verb("348")
# define RPL_ENDOFEXCEPTLIST    Verb("349")
# define RPL_VERSION            Verb("351")
# define RPL_NAMREPLY           Verb("353")
# define RPL_ENDOFNAMES         Verb("366")
# define RPL_LINKS              Verb("364")
# define RPL_ENDOFLINKS         Verb("365")
# define RPL_BANLIST            Verb("367")
# define RPL_ENDOFBANLIST       Verb("368")
# define RPL_ENDOFWHOWAS        Verb("369")
# define RPL_INFO               Verb("371")
# define RPL_ENDOFINFO          Verb("374")
# define RPL_MOTDSTART          Verb("375")
# define RPL_MOTD               Verb("372")
# define RPL_ENDOFMOTD          Verb("376")
# define RPL_WHOISHOST          Verb("378")
# define RPL_WHOISMODES         Verb("379")
# define RPL_YOUREOPER          Verb("381")
# define RPL_REHASHING          Verb("382")
# define RPL_TIME               Verb("391")
# define ERR_UNKNOWNERROR       Verb("400")
# define ERR_NOSUCHNICK         Verb("401")
# define ERR_NOSUCHSERVER       Verb("402")
# define ERR_NOSUCHCHANNEL      Verb("403")
# define ERR_CANNOTSENDTOCHAN   Verb("404")
# define ERR_TOOMANYCHANNELS    Verb("405")
# define ERR_WASNOSUCHNICK      Verb("406")
# define ERR_NOORIGIN           Verb("409")
# define ERR_INVALIDCAPCMD      Verb("410")
# define ERR_INPUTTOOLONG       Verb("417")
# define ERR_UNKNOWNCOMMAND     Verb("421")
# define ERR_NOMOTD             Verb("422")
# define ERR_ERRONEUSNICKNAME   Verb("432")
# define ERR_NICKNAMEINUSE      Verb("433")
# define ERR_NONICKNAMEGIVEN    Verb("431")
# define ERR_USERNOTINCHANNEL   Verb("441")
# define ERR_NOTONCHANNEL       Verb("442")
# define ERR_USERONCHANNEL      Verb("443")
# define ERR_NOTREGISTERED      Verb("451")
# define ERR_NEEDMOREPARAMS     Verb("461")
# define ERR_ALREADYREGISTERED  Verb("462")
# define ERR_PASSWDMISMATCH     Verb("464")
# define ERR_YOUREBANNEDCREEP   Verb("465")
# define ERR_CHANNELISFULL      Verb("471")
# define ERR_UNKNOWNMODE        Verb("472")
# define ERR_INVITEONLYCHAN     Verb("473")
# define ERR_BANNEDFROMCHAN     Verb("474")
# define ERR_BADCHANNELKEY      Verb("475")
# define ERR_BADCHANMASK        Verb("476")
# define ERR_NOPRIVILEGES       Verb("481")
# define ERR_CHANOPRIVSNEEDED   Verb("482")
# define ERR_CANTKILLSERVER     Verb("483")
# define ERR_NOOPERHOST         Verb("491")
# define ERR_UMODEUNKNOWNFLAG   Verb("501")
# define ERR_USERSDONTMATCH     Verb("502")
# define ERR_HELPNOTFOUND       Verb("524")
# define ERR_INVALIDKEY         Verb("525")
# define RPL_STARTTLS           Verb("670")
# define RPL_WHOISSECURE        Verb("671")
# define ERR_STARTTLS           Verb("691")
# define ERR_INVALIDMODEPARAM   Verb("696")
# define RPL_HELPSTART          Verb("704")
# define RPL_HELPTXT            Verb("705")
# define RPL_ENDOFHELP          Verb("706")
# define ERR_NOPRIVS            Verb("723")
# define RPL_LOGGEDIN           Verb("900")
# define RPL_LOGGEDOUT          Verb("901")
# define ERR_NICKLOCKED         Verb("902")
# define RPL_SASLSUCCESS        Verb("903")
# define ERR_SASLFAIL           Verb("904")
# define ERR_SASLTOOLONG        Verb("905")
# define ERR_SASLABORTED        Verb("906")
# define ERR_SASLALREADY        Verb("907")
# define RPL_SASLMECHS          Verb("908")

#endif
