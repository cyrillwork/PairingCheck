#include "configfileparser.h"

#include <iostream>
#include <fstream>


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"

using namespace rapidjson;


ConfigFileParser::ConfigFileParser(std::string name):
    fileName(name)
{

}

bool ConfigFileParser::Init()
{
    bool result = false;
    std::ifstream ifs(fileName);
    if(ifs.is_open())
    {
        Document document;
        IStreamWrapper wp(ifs);
        document.ParseStream(wp);

        for(auto it=document.MemberBegin(); it<document.MemberEnd(); ++it)
        {
            std::cout << "Element name=" << it->name.GetString() << std::endl;

            string node(it->name.GetString());

            if(node == "Type")
            {
                params = factoryParams(IParams::getTypeParam(it->value.GetString()));
            }

            if((node == "Params") && (params))
            {
               result = params->fromJSON(it->value);
            }

        }
    }
    else
    {
        std::cout << "Error. Config file not exist" << std::endl;
    }

    return result;
}

bool ConfigFileParser::generateJSON(TypeParam type)
{
    bool result = false;
    TypeParams temp_params = factoryParams(type);

    if(temp_params)
    {
        rapidjson::Document doc;

        auto& allocator = doc.GetAllocator();
        doc.SetObject();

        rapidjson::Value val;
        val.SetString(IParams::getStringType(type).c_str(), allocator);
        doc.AddMember("Type", val, allocator);

        temp_params->toJSON(doc);

        rapidjson::StringBuffer buffer;
        //rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);

        std::string filename("generate_");
        filename += temp_params->getName();
        filename += ".json";

        std::ofstream out(filename);
        if(!out)
        {
            std::cout << "Error open file " << filename << std::endl;
            return result;
        }

        out << buffer.GetString();
        out.close();

        result = true;
    }

    return result;
}

TypeParams ConfigFileParser::factoryParams(TypeParam type)
{
    TypeParams result = nullptr;

    if(type == TypeParam::RS232)
    {
        result = new ParamsRS232("/dev/ttyS0");
    }
    else
        if(type == TypeParam::UDP)
        {
            result = new ParamsUDP();
        }

    return result;
}

