#ifndef UDPINTERFACE_H
#define UDPINTERFACE_H

#include "iinterface.h"

class UDPInterface : public IInterface
{
public:

    UDPInterface(TypeParams _params);

    ~UDPInterface() override = default;

     const std::string name() override
        { return std::string("UDP"); }

    bool open() override;
    bool close() override;
    int read(char *data, int size, int timeout) override;
    int write(const char *data, int size) override;

private:
    bool isFirstByte = false;
};

#endif // UDPINTERFACE_H
