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
    None = 0,
    _CS5 = CS5,
    _CS6 = CS6,
    _CS7 = CS7,
    _CS8 = CS8,
};


class IParams
{
public:

    IParams(std::string dev): devPath(dev) {}

    virtual ~IParams() = default;

    virtual const std::string getName() noexcept = 0;

    virtual Parity getParity() { return Parity::None; }
    virtual void setParity(Parity parity) {}

    virtual int getBaudRate() { return 0; }
    virtual void setBaudRate(std::string _speed) {}

    virtual ByteSize getByteSize() { return ByteSize::None; }
    virtual void setByteSize(ByteSize byteSize) {}

    virtual void set9thBit(bool _is9thbit) {}
    virtual bool get9thBit() { return false; }

    const std::string getDevPath() { return devPath; }
    void setDevPath(std::string dev) { devPath = dev; }

protected:
    std::string devPath;
};


#endif // IPARAMS_H

