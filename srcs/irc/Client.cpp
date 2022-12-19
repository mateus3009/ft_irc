#include "irc/Client.hpp"

/* Client */

Client::Client(ClientStore& store, ConnectionSubscription& connection) :
    _store(&store),
    _connection(&connection),
    _nickname("*"),
    isRegistered(false),
    hasPassword(false),
    usingCap(false),
    isOperator(false) {}

std::string Client::getNickname(void) const { return _nickname; }

static bool validNicknameCharacter(unsigned char c)
{
    return ::isalnum(c) || c == '-' || c == '_';
}

void Client::setNickname(const std::string& nickname)
{
    if (nickname.size() > 20)
        throw InvalidNicknameException(
            "The nickname cannot have more than 20 characteres!");

    if (!allOf(nickname.begin(), nickname.end(), validNicknameCharacter))
        throw InvalidNicknameException(
            "The nickanme must match the expression [a-zA-Z\\-_]");
    try
    {
        _store->find(nickname);
        throw NicknameIsAlreadyInUseException(
            "There is a client with the same nickname!");
    }
    catch(const ClientStore::ClientNotFoundException&)
    {
        _nickname = nickname;
    }
}

std::string Client::getUsername(void) const { return _username; }

void Client::setUsername(const std::string& username)
{
    _username = username;
}

std::string Client::getHostname(void) const { return _hostname; }

void Client::setHostname(const std::string& hostname)
{
    _hostname = hostname;
}

std::string Client::getRealName(void) const { return _realName; }

void Client::setRealName(const std::string& realName)
{
    _realName = realName;
}

void Client::send(const Message& msg)
{
    std::string str = msg.toString();
    std::cout << getId() << "< " << str << std::endl;
    _connection->write(str);
}

int Client::getId(void) const { return _connection->getId(); }

void Client::close(void)
{
    _store->remove(_connection->getId());
    _connection->close();
}

Message::Source Client::getSource(void) const
{
    Message::Source src(_nickname);
    src.hostname = _hostname;
    src.username = _username;
    return src;
}

Client::InvalidNicknameException::InvalidNicknameException(const char* what)
    : Error(what) {}

Client::NicknameIsAlreadyInUseException::NicknameIsAlreadyInUseException(
    const char* what) : Error(what) {}

Client::AlreadyDefinedException::AlreadyDefinedException(const char* what)
    : Error(what) {}

bool operator==(const Client& c, const std::string n)
{
    return strcasecmp(c.getNickname().c_str(), n.c_str()) == 0;
}

/* ClientStore */

shared_ptr<Client> ClientStore::add(ConnectionSubscription& connection)
{
    shared_ptr<Client> c = shared_ptr<Client>::make_shared(
        new Client(*this, connection));
    if (_clients.insert(std::make_pair(c->getId(), c)).second == false)
        throw ClientAlreadyExistsException(
            "The client with this id already exists");
    return c;
}

void ClientStore::remove(const int& id)
{
    _clients.erase(id);
}

shared_ptr<Client> ClientStore::find(const std::string& nickname)
{
    NicknamePredicate p = { .nickname = nickname };
    std::map<int, shared_ptr<Client> >::iterator it =
        std::find_if(_clients.begin(), _clients.end(), p);
    if (it == _clients.end())
        throw ClientNotFoundException("Client Not Found!");
    return it->second;
}

void ClientStore::broadcast(const Message& msg, const std::string& author)
{
    for (std::map<int, shared_ptr<Client> >::iterator it = _clients.begin();
        it != _clients.end(); ++it)
    {
        if (it->second->isRegistered && it->second->getNickname() != author)
            it->second->send(msg);
    }
}

ClientStore::ClientNotFoundException::ClientNotFoundException(const char* what)
    : Error(what) {}

ClientStore::ClientAlreadyExistsException::ClientAlreadyExistsException(
    const char* what) : Error(what) {}

bool ClientStore::NicknamePredicate::operator()(
    std::pair<int, shared_ptr<Client> > item)
{
    return strcasecmp(
        item.second->getNickname().c_str(), nickname.c_str()) == 0;
}
