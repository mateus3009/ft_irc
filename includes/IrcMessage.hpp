#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <vector>
# include <stdexcept>
# include <cstring>

struct IrcMessageSource
{
    std::string nickname;
    std::string username;
    std::string hostname;
};

struct IrcMessage
{
    IrcMessageSource source;
    std::string verb;
    std::string message_to_send;
    std::vector<std::string> params;

    static IrcMessage parse(const char* data);
	private:
		static void validateData(const char* data, unsigned int *index);
		static void getInfoClient(const char* data, unsigned int *index,IrcMessage *message);
		static void get_command(const char* data, unsigned int *index,IrcMessage *message);
		static void get_params(const char* data, unsigned int *index,IrcMessage *message);
		static void get_message(const char* data, unsigned int index,IrcMessage *message);
};

#endif
