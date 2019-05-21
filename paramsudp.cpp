#include "paramsudp.h"

ParamsUDP::ParamsUDP(std::string dev): IParams(dev)
{

}

bool ParamsUDP::fromJSON(const rapidjson::Value &doc)
{
    bool result = false;
    const char* members[] = { "IP", "Port" };

    if(doc.IsObject())
    {
        bool isOK = true;

        for(size_t i = 0; i < sizeof(members)/sizeof(members[0]); ++i)
        {
            if(!doc.HasMember(members[i]))
            {
                isOK = false;
                break;
            }
        }

        if(isOK)
        {
            setDevPath(doc[members[0]].GetString());
            setPortUDP(doc[members[1]].GetString());
            result = true;
        }
    }
    return result;
}

void ParamsUDP::toJSON(rapidjson::Document& doc)
{
    auto& allocator = doc.GetAllocator();

    rapidjson::Value val;
    rapidjson::Value obj(rapidjson::kObjectType);

    val.SetString(getDevPath().c_str(), allocator);
    obj.AddMember("IP", val, allocator);

    val.SetString(std::to_string(portUDP).c_str(), allocator);
    obj.AddMember("Port", val, allocator);

    doc.AddMember("Params", obj, allocator);
}

uint16_t ParamsUDP::getPortUDP() const
{
    return portUDP;
}

void ParamsUDP::setPortUDP(const uint16_t&value)
{
    portUDP = value;
}

void ParamsUDP::setPortUDP(const char* value)
{
    portUDP = std::atoi(value);
}


