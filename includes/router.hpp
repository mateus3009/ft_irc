#ifndef ROUTER
# define ROUTER

# include <map>
# include <string>

# include "request.hpp"
# include "response.hpp"

class router
{
    public:
        typedef void (*route_handler)(request& req, response& res);

    private:
        static std::map<std::string, route_handler> _routes;

    public:
        static bool add(std::string verb, route_handler handler);

        static void route(request& req, response& res);
};

#endif
