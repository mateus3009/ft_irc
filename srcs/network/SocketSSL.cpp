#include "network/SocketSSL.hpp"

/* SSLContext */

SSLContext::SSLContext(const char* cert, const char* key) : _ctx(NULL)
{
    const SSL_METHOD* method = TLS_server_method();
    _ctx = SSL_CTX_new(method);
    if (!_ctx
        || SSL_CTX_use_certificate_file(_ctx, cert, SSL_FILETYPE_PEM) <= 0
        || SSL_CTX_use_PrivateKey_file(_ctx, key, SSL_FILETYPE_PEM) <= 0)
    {
        SSL_CTX_free(_ctx);
        throw Error(ERR_error_string(ERR_get_error(), NULL), ERR_get_error());
    }
}

SSLContext::~SSLContext() { SSL_CTX_free(_ctx); }

SSL_CTX* SSLContext::getCTX(void) const { return _ctx; }

/* SocketConnectionSSL */

SocketConnectionSSL::SocketConnectionSSL(const SSLContext* ctx, const int& id)
    : FileDescriptor(id), _ssl(NULL)
{
    _ssl = SSL_new(ctx->getCTX());
    if (!_ssl
        || SSL_set_fd(_ssl, SocketConnection::getId()) <= 0
        || SSL_accept(_ssl) <= 0)
    {
        SSL_free(_ssl);
        throw Error(ERR_error_string(ERR_get_error(), NULL), ERR_get_error());
    }
}

SocketConnectionSSL::~SocketConnectionSSL()
{
    if (!_ssl)
        return ;
    SSL_shutdown(_ssl);
    SSL_free(_ssl);
}

ssize_t SocketConnectionSSL::read(void *buf, size_t nbytes) const
{
    const int r = SSL_read(_ssl, buf, nbytes);
    if (r <= 0)
        throw Error(ERR_error_string(ERR_get_error(), NULL), ERR_get_error());
    return r;
}

ssize_t SocketConnectionSSL::write(const void *buf, size_t nbytes) const
{
    const int r = SSL_write(_ssl, buf, nbytes);
    if (r <= 0)
        throw Error(ERR_error_string(ERR_get_error(), NULL), ERR_get_error());
    return r;
}

/* SocketListenerSSL */

SocketListenerSSL::SocketListenerSSL(
    const SSLContext* ctx, const char* port, const char* hostname)
    : SocketListener(port, hostname), _ctx(ctx)
{
    if (!ctx)
        throw Error("SSLContext was not provided!", -1);
}

shared_ptr<SocketConnection> SocketListenerSSL::accept(void) const
{
    const int fd = ::accept(_id, NULL, NULL);
    if (fd < 0)
        throw Error();
    return shared_ptr<SocketConnection>::make_shared(
        new SocketConnectionSSL(_ctx, fd));
}
