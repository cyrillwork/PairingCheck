#ifndef IPARAMS_H
#define IPARAMS_H

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef _WIN32
    #include "termi_win/termios.h"
#else
    #include <termios.h>
#endif

#include <unistd.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/prettywriter.h"

class IParams;
using TypeParams = IParams*; //std::shared_ptr<IParams>;

enum class TypeParam : int
{
    None    = 0,
    RS232   = 1,
    UDP     = 2,
    //TCP     = 3
};

class IParams
{
public:
    IParams(std::string dev): devPath(dev) {}
    virtual ~IParams() = default;
    virtual const std::string getName() const = 0;
    virtual TypeParam getType() const = 0;

    const std::string getDevPath() { return devPath; }
    void setDevPath(std::string dev) { devPath = dev; }

    virtual bool fromJSON(const rapidjson::Value &doc) = 0;
    virtual void toJSON(rapidjson::Document &doc) = 0;

    static TypeParam getTypeParam(std::string name)
    {
        TypeParam result = TypeParam::None;
        if(name == "RS232")
        {
            result = TypeParam::RS232;
        }
        else
            if(name == "UDP")
            {
                result = TypeParam::UDP;
            }
        return result;
    }

    static std::string getStringType(TypeParam type)
    {
        std::string result;
        switch (type)
        {
            case TypeParam::None:
                result = "None";
            break;
            case TypeParam::RS232:
                result = "RS232";
            break;
            case TypeParam::UDP:
                result = "UDP";
            break;
        }

        return std::string(result);
    }

protected:
    std::string devPath;
};


#endif // IPARAMS_H

