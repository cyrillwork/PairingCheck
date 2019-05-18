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
                string type(it->value.GetString());

                if(type == "UDP")
                {
                    params = new ParamsUDP();
                }
                else
                    if(type == "RS232")
                    {
                        params = new ParamsRS();
                    }
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

