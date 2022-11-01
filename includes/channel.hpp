#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <map>

# include "channel_membership.hpp"

# define MODE_CHANNEL_BAN                   0x001
# define MODE_CHANNEL_EXCEPTION             0x002
# define MODE_CHANNEL_CLIENT_LIMIT          0x004
# define MODE_CHANNEL_INVITE_ONLY           0x008
# define MODE_CHANNEL_INVITE_EXCEPTION      0x016
# define MODE_CHANNEL_KEY_CHANNEL           0x032
# define MODE_CHANNEL_SECRET                0x064
# define MODE_CHANNEL_PROTECTED_TOPIC       0x128
# define MODE_CHANNEL_NO_EXTERNAL_MESSAGES  0x256

class channel
{
    const std::string                           _name;

    std::string                                 _topic;

    int                                         _modes;

    std::map<std::string, channel_membership>   _memberships;
};

#endif
