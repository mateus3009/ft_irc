#ifndef ROUTER
# define ROUTER

# include <map>
# include <string>

# include "request.hpp"
# include "response.hpp"

struct route { virtual void handle(const request& req, response& res) = 0; };

class router
{
    private:
        std::map<std::string, route*> _routes;

    public:
        bool add(std::string verb, route* route);

        void call(const request& req, response& res);

};

#endif
