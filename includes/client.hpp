#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <vector>

# include "channel.hpp"

# define MODE_USER_INVISIBLE    0x01
# define MODE_USER_OPER         0x02
# define MODE_USER_LOCAL_OPER   0x04
# define MODE_USER_REGISTERED   0x08
# define MODE_USER_WALLOPS      0x16

struct client
{
    const int                   _id;

    std::string                 _nickname;

    std::string                 _username;

    const std::string           _hostname;

    int                         _modes;

    std::vector<const channel*> _channels;
};

#endif
