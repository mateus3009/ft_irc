#ifndef message_HPP
# define message_HPP

# include <string>
# include <vector>
# include <stdexcept>
# include <cstring>

struct message
{
    struct source
    {
        std::string             nickname;
        std::string             username;
        std::string             hostname;
    } source;
    std::string                 verb;
    std::vector<std::string>    params;

    static message parse(const char* data);
};

#endif
