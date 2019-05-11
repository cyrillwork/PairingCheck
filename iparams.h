#ifndef IPARAMS_H
#define IPARAMS_H

#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

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


class IParams
{
public:

    IParams(std::string dev): devPath(dev) {}

    virtual ~IParams() = default;

    virtual const std::string getName() noexcept = 0;

    virtual Parity getParity() = 0;
    virtual void setParity(Parity parity) = 0;

    virtual int getBaudRate() = 0;
    virtual void setBaudRate(std::string _speed ) = 0;

    virtual ByteSize getByteSize() = 0;
    virtual void setByteSize(ByteSize byteSize) =  0;

    virtual void set9thBit(bool _is9thbit) = 0;
    virtual bool get9thBit() = 0;

    const std::string getDevPath() { return devPath; }
    void setDevPath(std::string dev) { devPath = dev; }

protected:
    std::string devPath;
};


#endif // IPARAMS_H

