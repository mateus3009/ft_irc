#ifndef PASS_HPP
# define PASS_HPP

# include <string>

# include "router.hpp"
# include "request.hpp"
# include "response.hpp"
# include "client_store.hpp"

# define ERR_NEEDMOREPARAMS     461
# define ERR_ALREADYREGISTERED  462
# define ERR_PASSWDMISMATCH     464

class pass : public route
{
    private:
        client_store&   _store;

        const std::string     _password;

    public:
        pass(client_store& store, const std::string& password);

        void handle(const request& req, response& res);
};

#endif
