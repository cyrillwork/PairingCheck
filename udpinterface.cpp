#include <iostream>

#include "udpinterface.h"
#include "const.h"

UDPInterface::UDPInterface(TypeParams _params):
    IInterface(_params)
{

#ifdef _WIN32
    WSADATA wsdata;
    WSAStartup(0x0101,&wsdata);
#endif

    params = dynamic_cast<TypeParamsUDP>(_params);
    if(params)
    {
        std::cout << "constructor UDP Interface devPath=" << params->getDevPath() << std::endl;
    }
    else
    {
        std::cout << "Fatal Error get TypeParamsUDP. Exit program" << std::endl;
        exit(0);
    }
}

bool UDPInterface::open()
{
    int result = -1;

    sockfd = ::socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd > 0)
    {
        memset(&sock_addr, 0, sizeof(struct sockaddr_in));

        sock_addr.sin_family = AF_INET;
        sock_addr.sin_port = htons(params->getPortUDP());
        sock_addr.sin_addr.s_addr = inet_addr(params->getDevPath().c_str());

        result = 0;
    }

    return (result == 0)?true:false;
}

bool UDPInterface::bind()
{
    int res = ::bind(sockfd, (struct sockaddr *)&sock_addr, sizeof(sock_addr) );

    return (res == 0) ? true : false;
}

bool UDPInterface::close()
{

#ifdef _WIN32
    WSACleanup();
#endif

    return ::close(sockfd);

}

int UDPInterface::read(char *data, int size, int timeout)
{
    if(check_sock(sockfd, timeout))
        return recvfrom(sockfd, data, size, /*MSG_DONTWAIT*/ 0, NULL, NULL);
    else
        return 0;
}

int UDPInterface::write(const char *data, int size)
{
    return sendto(sockfd, data, size, 0,
                  (struct sockaddr *)&sock_addr, sizeof(sock_addr));
}

bool UDPInterface::check_sock(int sock, int timeout)
{
    fd_set rset;
    struct timeval tv;

    FD_ZERO(&rset);
    FD_SET(sock, &rset);

    tv.tv_sec = timeout/1000000;
    tv.tv_usec = timeout - tv.tv_sec*1000000;

    return (select(sock + 1, &rset, NULL, NULL, &tv) > 0);
}
