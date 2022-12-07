#include "irc/Client.hpp"

Client::Client(IrcConnection& connection, ClientStore& store) : Modes(0), _nickname("*"), _hostname(connection.getHostname()), _connection(connection), _store(store){}

std::string Client::getNickname(void) const { return _nickname; }

static bool validNicknameCharacter(unsigned char c) { return ::isalnum(c) || c == '-' || c == '_'; }

void Client::setNickname(const std::string& nickname)
{
    if (!allOf(nickname.begin(), nickname.end(), validNicknameCharacter))
        throw Client::AlphaNumericConstraintViolationException("The nickname must be alphanumeric!");

    try
    {
        _store.find(nickname);
        throw Client::NicknameIsAlreadyInUseException("The nickname provided is already in use by another client!");
    }
    catch(const ClientStore::ClientNotFoundException& e)
    {
        _nickname = nickname;
    }

}

std::string Client::getUsername(void) const { return _username; }

void Client::setUsername(const std::string& username)
{
    if (!_username.empty())
        throw Client::UsernameIsAlreadyDefinedException("The username is already set! You can't change it anymore!");

    if (!allOf(username.begin(), username.end(), validNicknameCharacter))
        throw Client::AlphaNumericConstraintViolationException("The username must be alphanumeric!");

    _username = username;
}

std::string Client::getHostname(void) const { return _hostname; }

std::string Client::getRealName(void) const { return _realName; }

int Client::getIdClient(void) const { return _connection.getProxy().getId(); }

void Client::setRealName(const std::string& realName)
{
    _realName = realName;
}

void Client::send(const Message& msg) { _connection.send(msg); }

void Client::close(void)
{
    _connection.close();
}

Message::Source Client::getSource(void) const
{
    return (Message::Source) {
        .nickname = _nickname,
        .username = _username,
        .hostname = _hostname
    };
}

bool Client::Client::addChannel(std::string ch) {
	for (std::set<std::string>::iterator it = _channels.begin(); it != _channels.end(); ++it)
        std::cout << "|" << *it << "|" <<std::endl;
    return _channels.insert(ch).second;
}

Client::AlphaNumericConstraintViolationException::AlphaNumericConstraintViolationException(const char* what) : std::runtime_error(what) {}

Client::NicknameIsAlreadyInUseException::NicknameIsAlreadyInUseException(const char* what) : std::runtime_error(what) {}

Client::UsernameIsAlreadyDefinedException::UsernameIsAlreadyDefinedException(const char* what) : std::runtime_error(what) {}

bool operator==(const Client& l, const Client& r)
{
    return iequals(l.getNickname(), r.getNickname());
}

bool operator==(const Client& client, const std::string& nickname)
{
    return iequals(client.getNickname(), nickname);
}

bool operator<(const Client& l, const Client& r)
{
    return l.getNickname() < r.getNickname();
}

/* ClientStore */

shared_ptr<Client> ClientStore::add(IrcConnection& connection)
{
	std::cout << "criando cliente na lista: " << connection.getId()  << "com o hostname: " << connection.getHostname() << std::endl;

    shared_ptr<Client> client = new Client(connection, *this);
    if (!_clients.insert(std::make_pair(connection.getId(), client)).second)
        throw ClientStore::ClientAlreadyExists("The client already exists!");
    return client;
}

shared_ptr<Client> ClientStore::find(const std::string& nickname)
{
    NicknamePredicate p = { .nickname = nickname };
    ClientStore::iterator it = std::find_if(_clients.begin(), _clients.end(), p);
    if (it == _clients.end())
        throw ClientStore::ClientNotFoundException("Client Not Found!");
    return it->second;
}

void ClientStore::broadcast(const Message& msg)
{
    ClientMessageSender s = { .msg = msg };
    std::for_each(_clients.begin(), _clients.end(), s);
}

void ClientStore::remove(shared_ptr<Client> client)
{
	std::cout << "removendo cliente da lista: " << client->getIdClient() << std::endl;

    ClientPredicate p = { .client = client };
    ClientStore::iterator it = std::find_if(_clients.begin(), _clients.end(), p);
    if (it == _clients.end())
        throw ClientStore::ClientNotFoundException("Client Not Found!");
    _clients.erase(it);
}

ClientStore::ClientNotFoundException::ClientNotFoundException(const char* what) : std::runtime_error(what) {}

ClientStore::ClientAlreadyExists::ClientAlreadyExists(const char* what) : std::runtime_error(what) {}

bool ClientStore::NicknamePredicate::operator()(std::pair<int, shared_ptr<Client> > item)
{
    return item.second == nickname;
}

bool ClientStore::ClientPredicate::operator()(std::pair<int, shared_ptr<Client> > item)
{
    return item.second == client;
}

void ClientStore::ClientMessageSender::operator()(std::pair<int, shared_ptr<Client> > item)
{
    item.second->send(msg);
}
