#include "message.hpp"

message message::parse(const char* data)
{
        if (data == NULL || *data == '\0')
        throw std::runtime_error("No data was provided!");

    unsigned int index = 0;
    while (strchr(" \t", data[index]) != NULL)
        ++index;

    if (data[index] == '\0')
        throw std::runtime_error("The data providade was blank!");

    message      message;
    unsigned int    start;

    if (data[index] == ':')
    {
        start = ++index;
        while (strchr("!@ \t", data[index]) == NULL)
            ++index;
        message.source.nickname = std::string(data + start, data + index);

        if (data[index] == '!')
        {
            start = ++index;
            while (strchr("@ \t", data[index]) == NULL)
                ++index;
            message.source.username = std::string(data + start, data + index);
        }

        if (data[index] == '@')
        {
            start = ++index;
            while (strchr(" \t", data[index]) == NULL)
                ++index;
            message.source.hostname = std::string(data + start, data + index);
        }
    }

    while (strchr(" \t", data[index]) != NULL)
        ++index;
    start = index;

    while (strchr(" \t", data[index]) == NULL)
        ++index;
    message.verb = std::string(data + start, data + index);

    while (data[index] != '\0')
    {
        while (strchr(" \t", data[index]) != NULL)
            ++index;
        start = index;

        if (data[index] == ':')
            break ;

        while (strchr(" \t", data[index]) == NULL)
            ++index;
        message.params.push_back(std::string(data + start, data + index));
    }

    if (data[index] == ':')
    {
        start = ++index;

        while (data[index] != '\0')
            ++index;
        message.params.push_back(std::string(data + start, data + index));
    }

    return message;
}
