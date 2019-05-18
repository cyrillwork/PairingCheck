#ifndef IPARAMS_H
#define IPARAMS_H

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>


class IParams
{
public:
    IParams(std::string dev): devPath(dev) {}
    virtual ~IParams() = default;
    virtual const std::string getName() const = 0;

    const std::string getDevPath() { return devPath; }
    void setDevPath(std::string dev) { devPath = dev; }

protected:
    std::string devPath;
};


#endif // IPARAMS_H

