#ifndef CHANNEL_MEMBERSHIP_HPP
# define CHANNEL_MEMBERSHIP_HPP

# define MODE_MEMBERSHIP_FOUNDER    0x01
# define MODE_MEMBERSHIP_PROTECTED  0x02
# define MODE_MEMBERSHIP_OPERATOR   0x04
# define MODE_MEMBERSHIP_HALFOP     0x08
# define MODE_MEMBERSHIP_VOICE      0x16

# include "client.hpp"

class channel_membership
{
    const client*   client;

    int             modes;
};

#endif
