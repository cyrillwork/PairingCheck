//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#ifndef RS_INTERFACE_H
#define RS_INTERFACE_H

#include <iostream>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>


#include "const.h"
#include "abstract-interface.h"
#include "paramsrs.h"

using namespace std;

class RSInterface : public AbstractInterface
{
public:

    RSInterface(ParamsRS _params);

    ~RSInterface() override;

     const std::string name() override
        { return std::string("RS"); }

    bool open() override;
    bool close() override;
    int read(char *data, int size, int timeout) override;
    int write(const char *data, int size) override;
    int putCharWakeup(unsigned char symbol);

private:
    ParamsRS params;

    bool isFirstByte = false;

    int _channelId;   
    struct termios newtio0;
};

#endif // RS_INTERFACE_H
