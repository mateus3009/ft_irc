#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "NumericReply.hpp"
# include "CommandRouter.hpp"
# include "../utils/Tools.hpp"

struct Help
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Ping
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Pong
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Quit
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Pass
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Nick
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct User
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Cap
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct ErrorC
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Notice
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Privmsg
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Motd
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Mode
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Whois
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Join
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Topic
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Part
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Who
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Oper
{
    static bool isRegistered;

    static void handler(Payload& p);
};

struct Kill
{
    static bool isRegistered;

    static void handler(Payload& p);
};

#endif
