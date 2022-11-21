#ifndef MODES_HPP
# define MODES_HPP

# define MODE_MEMBERSHIP_FOUNDER     1
# define MODE_MEMBERSHIP_PROTECTED   2
# define MODE_MEMBERSHIP_OPERATOR    4
# define MODE_MEMBERSHIP_HALFOP      8
# define MODE_MEMBERSHIP_VOICE      16

# define MODE_CHANNEL_BAN                     1
# define MODE_CHANNEL_EXCEPTION               2
# define MODE_CHANNEL_CLIENT_LIMIT            4
# define MODE_CHANNEL_INVITE_ONLY             8
# define MODE_CHANNEL_INVITE_EXCEPTION       16
# define MODE_CHANNEL_KEY_CHANNEL            32
# define MODE_CHANNEL_SECRET                 64
# define MODE_CHANNEL_PROTECTED_TOPIC       128
# define MODE_CHANNEL_NO_EXTERNAL_MESSAGES  256

# define MODE_USER_INVISIBLE         1
# define MODE_USER_OPER              2
# define MODE_USER_LOCAL_OPER        4
# define MODE_USER_REGISTERED        8
# define MODE_USER_WALLOPS          16
# define MODE_USER_AUTORIZED        32
# define MODE_USER_CAP_NEGOTIATION  64

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
