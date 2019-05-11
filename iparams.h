#ifndef IPARAMS_H
#define IPARAMS_H

#include <string>

class IParams
{
public:

    IParams(std::string dev): devPath(dev) {}

    virtual ~IParams() = default;

    virtual const std::string getName() noexcept = 0;

    std::string getDevPath() const { return devPath; }
    void setDevPath(std::string devPath) { devPath = devPath; }

protected:
    std::string devPath;
};


#endif // IPARAMS_H

