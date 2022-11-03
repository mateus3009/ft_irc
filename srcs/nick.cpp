#include "nick.hpp"

nick::nick(client_store& store) : _store(store) {}

void nick::handle(const request& req, response& res)
{
    if (req.message.params.empty())
    {
        res.write(":server 431");
        return ;
    }

    std::string new_nick = *req.message.params.begin();
    // TODO retornar ERR_ERRONEUSNICKNAME  se o nickname estiver vazio ou for branco

    client* client = _store.find(req.id);
    if (!client->set_nickname(new_nick))
    {
        std::stringstream stream;

        stream << ":server 431 " << "<client>" << " " << new_nick << ":Nickname is already in use";
        res.write(stream.str());
        return ;
    }
    // TODO se estiver autenticado: avisar outros clients que ele mudou de nome
}
