#ifndef UDPINTERFACE_H
#define UDPINTERFACE_H

#include <cstring>
#include <sys/types.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif

#include "paramsudp.h"
#include "iinterface.h"


class UDPInterface : public IInterface
{
public:

    UDPInterface(TypeParams _params);

    ~UDPInterface() override = default;

     const std::string name() override
        { return std::string("UDP"); }

    bool open() override;
    bool bind() override;
    bool close() override;
    int read(char *data, int size, int timeout) override;
    int write(const char *data, int size) override;

    bool check_sock(int sock, int timeout);

private:
    sockaddr_in sock_addr;
    bool isFirstByte = false;
    int sockfd;

    TypeParamsUDP params;
};

#endif // UDPINTERFACE_H
