#ifndef PARAMSRS_H
#define PARAMSRS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <string>
#include <map>
#include <iostream>

using namespace std;


enum class Parity
{
    None = 0,
    Odd  = (PARENB | PARODD),
    Even = PARENB
};

enum ByteSize
{
    _CS5 = CS5,
    _CS6 = CS6,
    _CS7 = CS7,
    _CS8 = CS8
};

class ParamsRS
{
public:
    ParamsRS();

    ParamsRS (ParamsRS &params);

    ParamsRS(string devPath, Parity parity, int speed, ByteSize byteSize);

    string getDevPath() { return devPath; }
    void setDevPath(string devPath) { this->devPath = devPath; }

    Parity getParity() { return parity; }
    void setParity(Parity parity) { this->parity = parity; }

    int getBaudRate() { return speed; }
    void setBaudRaet( string _speed ) { this->speed = this->baudeRate[_speed]; }

    ByteSize getByteSize() { return byteSize; }
    void setByteSize(ByteSize byteSize) { this->byteSize = byteSize; }

    void set9thBit(bool _is9thbit) { this->Is9thbit = _is9thbit; }
    bool get9thBit() { return this->Is9thbit; }

private:
    string devPath;
    Parity parity; // "None"
    int speed;
    ByteSize byteSize;

    bool Is9thbit = false;

    map <string, int> baudeRate =
    {
        { "50",  B50 },
        { "75",  B75 },
        { "110", B110 },
        { "134", B134 },
        { "150", B150 },
        { "200", B200 },
        { "300", B300 },
        { "600", B600 },
        { "1200",  B1200 },
        { "1800",  B1800 },
        { "2400",  B2400 },
        { "4800",  B4800 },
        { "9600",  B9600 },
        { "19200", B19200 },
        { "38400", B38400 },
        { "57600", B57600 },
        { "115200", B115200 },
        { "230400", B230400 }
    };

};

#endif // PARAMSRS_H
