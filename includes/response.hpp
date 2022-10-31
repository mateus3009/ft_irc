#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "connection_handler.hpp"

class connection_handler;

class response
{
    private:
        connection_handler*  _connection;

    public:
        response(connection_handler* connection);

        void write(const std::string& msg);

        void quit(void);

};

#endif
