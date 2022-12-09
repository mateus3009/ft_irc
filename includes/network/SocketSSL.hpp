#ifndef SOCKETSSL_HPP
# define SOCKETSSL_HPP

# include <openssl/ssl.h>
# include <openssl/err.h>

# include "Socket.hpp"

class SSLContext
{
    private:
        SSL_CTX* _ctx;

    public:
        SSLContext(const char* cert, const char* key);

        virtual ~SSLContext();

        SSL_CTX* getCTX(void) const;
};

class SocketConnectionSSL : public virtual SocketConnection
{
    private:
        SSL* _ssl;

    public:
        SocketConnectionSSL(const SSLContext* ctx, const int& id = INVALID_FD);

        virtual ~SocketConnectionSSL();

        virtual ssize_t read(void *buf, size_t nbytes) const;

        virtual ssize_t write(const void *buf, size_t nbytes) const;

};

class SocketListenerSSL : public virtual SocketListener
{
    private:
        const SSLContext* _ctx;

    public:
        SocketListenerSSL(
            const SSLContext* ctx,
            const char* port = "0",
            const char* hostname = NULL);

        virtual shared_ptr<SocketConnection> accept(void) const;

};

#endif
