#include "IrcMessage.hpp"

void IrcMessage::validateData(const char* data, unsigned int *index){
	
	 if (data == NULL || *data == '\0')
        throw std::runtime_error("No data was provided!");
    while (strchr(" \t", data[*index]) != NULL)
        ++index;
    if (data[*index] == '\0')
        throw std::runtime_error("The data providade was blank!");

}

void IrcMessage::getInfoClient(const char* data, unsigned int *index,IrcMessage *message){
	unsigned int    start;

	start = ++*index;
        while (strchr("!@ \t", data[*index]) == NULL)
            ++*index;
        message->source.nickname = std::string(data + start, data + *index);
        if (data[*index] == '!')
        {
            start = ++*index;
            while (strchr("@ \t", data[*index]) == NULL)
                ++*index;
            message->source.username = std::string(data + start, data + *index);
        }
        if (data[*index] == '@')
        {
            start = ++*index;
            while (strchr(" \t", data[*index]) == NULL)
                ++*index;
            message->source.hostname = std::string(data + start, data + *index);
        }
}

void IrcMessage::get_command(const char* data, unsigned int *index,IrcMessage *message){
	while (strchr(" \t", data[*index]) != NULL)
        ++*index;
    unsigned int start = *index;
    while (strchr(" \t", data[*index]) == NULL)
        ++*index;
    message->verb = std::string(data + start, data + *index);
}
void IrcMessage::get_message(const char* data, unsigned int index,IrcMessage *message){
	unsigned int start = index;

	while (strchr(" \t", data[index]) != NULL)
            ++index;
	while (data[index] != '\0')
		index++;
	message->message_to_send = std::string(data + start, data + index);

}
void IrcMessage::get_params(const char* data, unsigned int *index,IrcMessage *message){
	unsigned int start;
	get_message(data, *index, message);
	while (data[*index] != '\0')
    {
        while (strchr(" \t", data[*index]) != NULL)
            ++*index;
        start = *index;

        if (data[*index] == ':')
            break ;

        while (strchr(" \t", data[*index]) == NULL)
            ++*index;
        message->params.push_back(std::string(data + start, data + *index));
    }
	if (data[*index] == ':')
    {
        start = ++*index;

        while (data[*index] != '\0')
            ++*index;
        message->params.push_back(std::string(data + start, data + *index));
    }
}

IrcMessage IrcMessage::parse(const char* data)
{
	IrcMessage      message;
	unsigned int 	index = 0;

	IrcMessage::validateData(data, &index);
    if (data[index] == ':'){
        IrcMessage::getInfoClient(data, &index, &message);
	}
    IrcMessage::get_command(data, &index, &message);
    IrcMessage::get_params(data, &index, &message);
    return message;
}
