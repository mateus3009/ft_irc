#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "connection_handler.hpp"
# include "shared_ptr.hpp"

class connection_handler;

class response
{
    private:
        shared_ptr<connection_handler>  _connection;

    public:
        response(shared_ptr<connection_handler> connection);

        void write(const std::string& msg);

        void quit(void);

};

#endif
