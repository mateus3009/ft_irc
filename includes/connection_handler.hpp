#ifndef CONNECTION_HANDLER_HPP
# define CONNECTION_HANDLER_HPP

# include <vector>

# include "socket_connection.hpp"
# include "input_buffer.hpp"
# include "output_buffer.hpp"
# include "message.hpp"
# include "response.hpp"
# include "connection.hpp"

class response;

class connection_handler
{
    private:
        socket_connection   _connection;

        input_buffer        _input;

        output_buffer       _output;


    public:
        bool closing;

        connection_handler(const socket_connection& connection);

        int get_id(void) const;

        std::vector<message> read(void);

        void write(const std::string& str);

        void flush(void);

        std::string get_hostname(void) const;

        response get_response(void);

        void close(void);

        size_t queued(void) const;

};

bool operator==(const connection_handler& l, const int& r);

#endif
