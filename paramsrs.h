#ifndef PARAMSRS_H
#define PARAMSRS_H

#include "iparams.h"

#include <memory>
#include <unordered_map>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef _WIN32
    //#include "termi_win/termios.h"
    #include "serial/win_serial.h"
    using namespace win_serial;
#else
    #include <termios.h>
#endif



enum class Parity
{
    None = 0,
    Odd  = (PARENB | PARODD),
    Even = PARENB
};

enum ByteSize
{
    None = 0,
    _CS5 = CS5,
    _CS6 = CS6,
    _CS7 = CS7,
    _CS8 = CS8,
};


class ParamsRS232;
//using TypeParamsRS = ParamsRS232*;
using TypeParamsRS = std::shared_ptr<ParamsRS232>;

using std::string;

class ParamsRS232: public IParams
{
public:

    ParamsRS232 (ParamsRS232 &params);

    ParamsRS232(string _devPath = "/dev/ttyS0", Parity _parity = Parity::None,
                            int _speed = B9600, ByteSize _byteSize = ByteSize::_CS8);

    const string getName() const override { return string("RS232"); }

    TypeParam getType() const override { return TypeParam::RS232; }

    Parity getParity() { return parity; }
    void setParity(Parity parity) { this->parity = parity; }

    speed_t getBaudRate() { return static_cast<speed_t>(speed); }

    std::string getBaudRateString();
    std::string getByteSizeString();

    void setBaudRate ( string _speed );

    ByteSize getByteSize() { return byteSize; }
    void setByteSize(ByteSize byteSize) { this->byteSize = byteSize; }

    void set9thBit(bool _is9thbit) { this->Is9thbit = _is9thbit; }
    bool get9thBit() { return this->Is9thbit; }

    virtual bool fromJSON(const rapidjson::Value &doc) override;

    virtual void toJSON(rapidjson::Document &doc) override;

private:
    Parity parity; // "None"
    int speed;
    ByteSize byteSize;

    bool Is9thbit = false;
    std::unordered_map <string, int> baudeRate =
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
