#ifndef SERVER_HPP
# define SERVER_HPP

# include "Socket.hpp"
# include "Connection.hpp"

template <typename T>
class Server
{
    private:
        SocketListener              _listener;

        std::vector<pollfd>         _poll;

        std::vector<Connection<T>*> _connections;

    public:
        Server(const char*, const char* port) : _listener(port), _poll(), _connections()
        {
            _poll.push_back((pollfd) { .fd = _listener.getId(), .events = POLLIN });
            _connections.push_back(NULL);
        }

        void listen(void)
        {
            while (true)
            {
                if (poll(_poll.data(), _poll.size(), 500) < 0)
                    throw std::runtime_error("");

                size_t index = 0;

                if (_poll[index].revents & POLLIN && _poll[index].fd == _listener.getId())
                {
                    Connection<T>* con = new Connection<T>(_listener.accept());
                    _connections.push_back(con);
                    _poll.push_back((pollfd) { .fd = con->getId(), .events = POLLIN });
                }

                ++index;

                while(index < _poll.size())
                {
                    if (_poll[index].revents & POLLIN)
                        _connections[index]->receive();

                    if (_poll[index].revents & POLLOUT)
                        _connections[index]->send();

                    if (_connections[index]->isQueued())
                        _poll[index].events |= (POLLWRNORM | POLLOUT);
                    else
                        _poll[index].events &= ~(POLLWRNORM | POLLOUT);

                    if (_connections[index]->isClosing() || _poll[index].revents & (POLLHUP | POLLERR | POLLNVAL))
                    {
                        _connections[index]->close();
                        _poll.erase(_poll.begin() + index);
                        delete _connections[index];
                        _connections.erase(_connections.begin() + index);
                        continue ;
                    }

                    ++index;
                }
            }
        }
};

#endif
