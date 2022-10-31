#ifndef message_HPP
# define message_HPP

# include <string>
# include <vector>
# include <stdexcept>
# include <cstring>
# include <sstream>

struct message
{
    struct source
    {
        std::string             nickname;
        std::string             username;
        std::string             hostname;
    } source;
    std::string                 verb;
    std::string                 message_to_send;
    std::vector<std::string>    params;

    static message parse(const char* data);

	private:
		static void validateData(const char* data, unsigned int *index);

		static void getInfoClient(const char* data, unsigned int *index,message *message);

		static void get_command(const char* data, unsigned int *index,message *message);

		static void get_params(const char* data, unsigned int *index,message *message);

		static void get_message(const char* data, unsigned int index,message *message);

    public:
        std::string to_string(void) const;

};

#endif
