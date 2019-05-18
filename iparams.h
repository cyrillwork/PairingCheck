#ifndef IPARAMS_H
#define IPARAMS_H

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"

class IParams;
using TypeParams = IParams*; //std::shared_ptr<IParams>;

class IParams
{
public:
    IParams(std::string dev): devPath(dev) {}
    virtual ~IParams() = default;
    virtual const std::string getName() const = 0;

    const std::string getDevPath() { return devPath; }
    void setDevPath(std::string dev) { devPath = dev; }

    virtual bool fromJSON(const rapidjson::Value &doc) = 0;

protected:
    std::string devPath;
};


#endif // IPARAMS_H

