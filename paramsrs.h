#ifndef PARAMSRS_H
#define PARAMSRS_H

#include "iparams.h"

#include <memory>
#include <unordered_map>
#include <iostream>

using namespace std;


class ParamsRS;
using TypeParamsRS = std::unique_ptr<ParamsRS>;

class ParamsRS: public IParams
{
public:
    ParamsRS();

    ParamsRS (ParamsRS &params);

    ParamsRS(string devPath, Parity parity, int speed, ByteSize byteSize);

    const string getName() noexcept override { return string("Params RS-231"); }

    Parity getParity() override { return parity; }
    void setParity(Parity parity) override { this->parity = parity; }

    int getBaudRate() override { return speed; }
    void setBaudRate ( string _speed ) override;

    ByteSize getByteSize() override { return byteSize; }
    void setByteSize(ByteSize byteSize) override { this->byteSize = byteSize; }

    void set9thBit(bool _is9thbit) override { this->Is9thbit = _is9thbit; }
    bool get9thBit() override { return this->Is9thbit; }

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
