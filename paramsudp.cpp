#include "paramsudp.h"

ParamsUDP::ParamsUDP(std::string dev): IParams(dev)
{

}

bool ParamsUDP::fromJSON(const rapidjson::Value &doc)
{
    bool result = false;

    if(doc.IsObject())
    {
    }


    return result;
}

void ParamsUDP::toJSON(rapidjson::Document& doc)
{
}

