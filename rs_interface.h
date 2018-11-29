#ifndef RS_INTERFACE_H
#define RS_INTERFACE_H

#include <iostream>
#include <string>
#include <map>

#include "const.h"
#include "abstract-interface.h"

using namespace std;

class RSInterface : public AbstractInterface
{

public:
    RSInterface() {};
    RSInterface(string devPath);
    ~RSInterface();

    const char* name() { return "RS"; }

    bool open();
    bool close();
    int read(char *data, int size, int timeout);
    int write(const char *data, int size);

private:
    map <int, int> _baudRate;
    map <string, int> _parity;
    map <int, int> _byteSize;

    int _channelId;
    string devPath;

};

#endif // RS_INTERFACE_H