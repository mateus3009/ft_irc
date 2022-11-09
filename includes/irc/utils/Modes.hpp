#ifndef MODES_HPP
# define MODES_HPP

# define MODE_MEMBERSHIP_FOUNDER    0x01
# define MODE_MEMBERSHIP_PROTECTED  0x02
# define MODE_MEMBERSHIP_OPERATOR   0x04
# define MODE_MEMBERSHIP_HALFOP     0x08
# define MODE_MEMBERSHIP_VOICE      0x16

# define MODE_CHANNEL_BAN                   0x001
# define MODE_CHANNEL_EXCEPTION             0x002
# define MODE_CHANNEL_CLIENT_LIMIT          0x004
# define MODE_CHANNEL_INVITE_ONLY           0x008
# define MODE_CHANNEL_INVITE_EXCEPTION      0x016
# define MODE_CHANNEL_KEY_CHANNEL           0x032
# define MODE_CHANNEL_SECRET                0x064
# define MODE_CHANNEL_PROTECTED_TOPIC       0x128
# define MODE_CHANNEL_NO_EXTERNAL_MESSAGES  0x256

# define MODE_USER_INVISIBLE    0x01
# define MODE_USER_OPER         0x02
# define MODE_USER_LOCAL_OPER   0x04
# define MODE_USER_REGISTERED   0x08
# define MODE_USER_WALLOPS      0x16
# define MODE_USER_AUTORIZED    0x36

class Modes
{
    private:
        unsigned int    _modes;

    public:
        Modes(const unsigned int& modes);

        virtual ~Modes();

        virtual unsigned int getModes(void) const;

        virtual bool hasAnyModes(const unsigned int& modes);

        virtual bool hasAllModes(const unsigned int& modes);

        virtual void setModes(const unsigned int& modes);

        virtual void unsetModes(const unsigned int& modes);

};

#endif
