#include "udpinterface.h"

UDPInterface::UDPInterface(TypeParams _params):
    IInterface(std::move(_params))
{

}

bool UDPInterface::open()
{
    return false;
}

bool UDPInterface::close()
{
    return false;
}

int UDPInterface::read(char *data, int size, int timeout)
{
    return 0;
}

int UDPInterface::write(const char *data, int size)
{
    return 0;
}
