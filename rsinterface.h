//This is an open source non-commercial project. Dear PVS-Studio, please check it.
#ifndef RS_INTERFACE_H
#define RS_INTERFACE_H

#include <iostream>
#include <map>
#include <cstring>

#include "serial/iserial.h"

#include "const.h"
#include "iinterface.h"
#include "paramsrs.h"

#ifdef _WIN32
    #include "serial/winserial.h"
    using namespace win_serial;
#else
    #include "serial/linuxserial.h"
#endif


class RSInterface : public IInterface
{
public:

    RSInterface(TypeParams _params, PtrSerial _serial);

    ~RSInterface() override;

     const std::string name() override
        { return std::string("RS"); }

    bool open() override;
    bool close() override;
    /* timeout - micro seconds*/
    int read(char *data, int size, int timeout) override;

    int write(const char *data, int size) override;
    int putCharWakeup(unsigned char symbol);

private:
    bool isFirstByte = false;
    int _channelId;

    termios newtio0;
    TypeParamsRS params;

    PtrSerial serial;
};

#endif // RS_INTERFACE_H
