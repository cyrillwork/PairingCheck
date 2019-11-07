#ifndef UDPPARAMS_H
#define UDPPARAMS_H

#include "iparams.h"

class ParamsUDP;
//using TypeParamsUDP = ParamsUDP*;
using TypeParamsUDP = std::shared_ptr<ParamsUDP>;

class ParamsUDP : public IParams
{
public:
    ParamsUDP():IParams("127.0.0.1") {}
    ParamsUDP(std::string dev);

    const std::string getName() const override { return std::string("UDP"); }
    TypeParam getType() const override { return TypeParam::UDP; }

    virtual bool fromJSON(const rapidjson::Value &doc) override;
    virtual void toJSON(rapidjson::Document &doc) override;

    uint16_t getPortUDP() const;
    void setPortUDP(const uint16_t&value);
    void setPortUDP(const char*value);

private:

    uint16_t portUDP;
};

#endif // UDPPARAMS_H
