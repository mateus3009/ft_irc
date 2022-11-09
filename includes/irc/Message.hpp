#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <vector>
# include <cstring>
# include <sstream>
# include <iostream>

struct Message
{
    struct Source
    {
        std::string             nickname;

        std::string             username;

        std::string             hostname;

    } source;

    std::string                 verb;

    std::vector<std::string>    params;

    Message(void);

    Message(const std::string& str);

    Message(const char* str);

    ~Message();

    Message& operator=(const Message& other);

    bool empty(void) const;

    std::string toString(void) const;

    void clear(void);

};

struct Verb
{
    const std::string v;

    Verb(const std::string& verb);
};

Message operator<<(const Message& msg, const Message::Source& src);

Message operator<<(const Message& msg, const int& reply);

Message operator<<(const Message& msg, const Verb& Verb);

Message operator<<(const Message& msg, const std::string& param);

std::ostream& operator<<(std::ostream& stream, const Message& msg);

#endif
