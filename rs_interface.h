//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#ifndef RS_INTERFACE_H
#define RS_INTERFACE_H

#include <iostream>
#include <string>
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
    RSInterface() {};
    //RSInterface(string devPath);
    RSInterface(ParamsRS _params);

    ~RSInterface();

    const char* name() { return "RS"; }

    bool open();
    bool close();
    int read(char *data, int size, int timeout);
    int write(const char *data, int size);
    int putCharWakeup(unsigned char symbol);

private:
    //map <int, int> _baudRate;
    //map <string, int> _parity;
    //map <int, int> _byteSize;
    //string devPath;

    ParamsRS params;

    bool isFirstByte = false;

    int _channelId;   
    struct termios newtio0;
};

#endif // RS_INTERFACE_H
