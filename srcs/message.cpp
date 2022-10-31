#include "message.hpp"

void message::validateData(const char* data, unsigned int *index)
{
    if (data == NULL || *data == '\0')
        throw std::runtime_error("No data was provided!");
    while (strchr(" \t\r\n", data[*index]) != NULL)
        ++index;
    if (data[*index] == '\0' || strchr("\r\n", *data) != NULL)
        throw std::runtime_error("The data providade was blank!");
}

void message::getInfoClient(const char* data, unsigned int *index,message *message)
{
	unsigned int    start;

	start = ++*index;
        while (data[*index] != '\0' && strchr("!@ \t\r\n", data[*index]) == NULL)
            ++*index;
        message->source.nickname = std::string(data + start, data + *index);
        if (data[*index] == '!')
        {
            start = ++*index;
            while (data[*index] != '\0' && strchr("@ \t\r\n", data[*index]) == NULL)
                ++*index;
            message->source.username = std::string(data + start, data + *index);
        }
        if (data[*index] == '@')
        {
            start = ++*index;
            while (data[*index] != '\0' && strchr(" \t\r\n", data[*index]) == NULL)
                ++*index;
            message->source.hostname = std::string(data + start, data + *index);
        }
}

void message::get_command(const char* data, unsigned int *index,message *message)
{
	while (data[*index] != '\0' && strchr(" \t\r\n", data[*index]) != NULL)
        ++*index;
    unsigned int start = *index;
    while (data[*index] != '\0' && strchr(" \t\r\n", data[*index]) == NULL)
        ++*index;
    message->verb = std::string(data + start, data + *index);
}

void message::get_message(const char* data, unsigned int index, message *message)
{
	unsigned int start = index;

	while (strchr(" \t", data[index]) != NULL)
            ++index;
	while (data[index] != '\0')
		index++;
	message->message_to_send = std::string(data + start, data + index);

}

void message::get_params(const char* data, unsigned int *index, message *message)
{
	unsigned int start;
	get_message(data, *index, message);
	while (data[*index] != '\0' && strchr("\r\n", data[*index]) == NULL)
    {
        while (data[*index] != '\0' && strchr(" \t\r\n", data[*index]) != NULL)
            ++*index;
        start = *index;

        if (data[*index] == ':')
            break ;

        while (data[*index] != '\0' && strchr(" \t\r\n", data[*index]) == NULL)
            ++*index;
        message->params.push_back(std::string(data + start, data + *index));
    }
	if (data[*index] == ':')
    {
        start = ++*index;

        while (data[*index] != '\0' && strchr(" \t\r\n", data[*index]) == NULL)
            ++*index;
        message->params.push_back(std::string(data + start, data + *index));
    }
}

message message::parse(const char* data)
{
	message      message;
	unsigned int 	index = 0;

	message::validateData(data, &index);
    if (data[index] == ':'){
        message::getInfoClient(data, &index, &message);
	}
    message::get_command(data, &index, &message);
    message::get_params(data, &index, &message);
    return message;
}

std::string message::to_string(void) const
{
    std::stringstream stream;

    stream
        << ':' << source.nickname
        << '!' << source.username
        << '@' << source.hostname
        << ' ' << verb;
    for (std::vector<std::string>::const_iterator it = params.begin(); it != params.end(); ++it)
        stream << " " << *it;
    return stream.str();
}