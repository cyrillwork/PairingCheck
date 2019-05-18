//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#ifndef RS_INTERFACE_H
#define RS_INTERFACE_H

#include <iostream>
#include <map>
#include <cstring>


#include "const.h"
#include "iinterface.h"
#include "paramsrs.h"

class RSInterface : public IInterface
{
public:

    RSInterface(TypeParams _params);

    ~RSInterface() override;

     const std::string name() override
        { return std::string("RS"); }

    bool open() override;
    bool close() override;
    int read(char *data, int size, int timeout) override;
    int write(const char *data, int size) override;
    int putCharWakeup(unsigned char symbol);

private:
    //ParamsRS params;

    bool isFirstByte = false;

    int _channelId;   
    struct termios newtio0;
    TypeParamsRS params;
};

#endif // RS_INTERFACE_H