#include "irc/Message.hpp"

std::string Message::Source::toString(void) const
{
    std::stringstream stream;

    if (!this->nickname.empty())
    {
        stream << ':' << this->nickname;
        if (!this->username.empty())
            stream << '!' << this->username;
        if (!this->hostname.empty())
            stream << '@' << this->hostname;
        stream << ' ';
    }
    return stream.str();
}

Message::Message(void) {}

Message::Message(const std::string& str)
{
    *this = str.c_str();
}

Message::Message(const char* str)
{
    if (str == NULL || *str == '\0')
        return ;

    unsigned int    start = 0;
    unsigned int    index = 0;

    while (strchr(" \t", str[index]) != NULL)
        ++index;

    /* Source */
    if (str[index] == ':')
    {

        /* Nickname */

        start = ++index;
        while (str[index] != '\0' && strchr("!@ \t", str[index]) == NULL)
            ++index;
        this->source.nickname = std::string(str + start, str + index);

        /* Username */

        if (str[index] == '!')
        {
            start = ++index;
            while (str[index] != '\0' && strchr("@ \t", str[index]) == NULL)
                ++index;
            this->source.username = std::string(str + start, str + index);
        }

        /* Hostname */

        if (str[index] == '@')
        {
            start = ++index;
            while (str[index] != '\0' && strchr(" \t", str[index]) == NULL)
                ++index;
            this->source.hostname = std::string(str + start, str + index);
        }
    }

    /* Verb */

    while (str[index] != '\0' && strchr(" \t", str[index]) != NULL)
        ++index;
    start = index;
    while (str[index] != '\0' && strchr(" \t", str[index]) == NULL)
        ++index;
    this->verb = std::string(str + start, str + index);

    /* Params */

    while (str[index] != '\0' && strchr("", str[index]) == NULL)
    {
        while (str[index] != '\0' && strchr(" \t", str[index]) != NULL)
            ++index;

        if (str[index] == ':')
            break ;

        start = index;
        while (str[index] != '\0' && strchr(" \t", str[index]) == NULL)
            ++index;
        this->params.push_back(std::string(str + start, str + index));
    }

    /* Trailing Param */

    if (str[index] == ':')
    {
        start = ++index;
        while (str[index] != '\0')
            ++index;
        this->params.push_back(std::string(str + start, str + index));
    }
}

Message::~Message() {}

Message& Message::operator=(const Message& other)
{
    this->source.nickname   = other.source.nickname;
    this->source.username   = other.source.username;
    this->source.hostname   = other.source.hostname;
    this->verb              = other.verb;
    this->params            = other.params;

    return *this;
}

bool Message::empty(void) const
{
    return this->source.nickname.empty()
        && this->source.username.empty()
        && this->source.hostname.empty()
        && this->verb.empty()
        && this->params.empty();
}


std::string Message::toString(void) const
{
    std::stringstream stream;

    stream << this->source.toString();

    stream << this->verb;

    for (std::vector<std::string>::const_iterator it = params.begin(); it != params.end(); ++it)
    {
        stream << ' ';
        if (it->find(' ') != std::string::npos || it + 1 == params.end())
            stream << ':';
        stream << *it;
    }

    return stream.str();
}

void Message::clear(void)
{
    this->source.nickname.clear();
    this->source.username.clear();
    this->source.hostname.clear();
    this->verb.clear();
    this->params.clear();
}

Verb::Verb(const std::string& verb) : v(verb) {}

Message operator<<(const Message& msg, const Message::Source& src)
{
    Message m = msg;
    m.source.nickname = src.nickname;
    m.source.username = src.username;
    m.source.hostname = src.hostname;
    return m;
}

Message operator<<(const Message& msg, const Verb& verb)
{
    Message m = msg;
    m.verb = verb.v;
    return m;
}

Message operator<<(const Message& msg, const std::string& param)
{
    Message m = msg;
    m.params.push_back(param);
    return m;
}

std::ostream& operator<<(std::ostream& stream, const Message& msg)
{
    return stream << msg.toString();
}
