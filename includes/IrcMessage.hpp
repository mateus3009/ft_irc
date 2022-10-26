#ifndef IRCMESSAGE_HPP
# define IRCMESSAGE_HPP

# include <string>
# include <vector>
# include <stdexcept>
# include <cstring>

struct IrcMessageSource
{
    std::string nickname;
    std::string username;
    std::string hostname;
};

struct IrcMessage
{
    IrcMessageSource source;
    std::string verb;
    std::vector<std::string> params;

    static IrcMessage parse(const char* data);
};

#endif
