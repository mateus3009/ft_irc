#include <iostream>

#include "network/SocketSSL.hpp"
#include "irc/Server.hpp"

int main(int argc, char** argv)
{
    //const SSLContext ctx("./cert.pem", "./key.pem");

    //const SocketListenerSSL listener(&ctx);

    char* port = (char *)"0";
    if (argc > 1)
        port = argv[1];

    char* hostname = (char *)NULL;
    if (argc > 2)
        hostname = argv[2];

    Server s(port, hostname);

    return 0;
};
