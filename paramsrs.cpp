#include "paramsrs.h"


ParamsRS232::ParamsRS232(ParamsRS232 &params):
    IParams(params.getDevPath()),
    parity(params.getParity()),
    speed(params.getBaudRate()),
    byteSize(params.getByteSize()),
    Is9thbit(params.Is9thbit)
{

}

ParamsRS232::ParamsRS232(string _devPath, Parity _parity, int _speed, ByteSize _byteSize):
    IParams(_devPath),
    parity(_parity),

    byteSize(_byteSize)
{
    speed = _speed;
}

std::string ParamsRS232::getBaudRateString()
{
    std::string result = {""};

    for(auto it: baudeRate)
    {
        if(it.second == speed)
        {
            return string(it.first);
        }
    }

    return string(result);
}

std::string ParamsRS232::getByteSizeString()
{
    std::string res="";
    switch(byteSize)
    {
        case ByteSize::_CS5: res= "CS5"; break;
        case ByteSize::_CS6: res= "CS6"; break;
        case ByteSize::_CS7: res= "CS7"; break;
        case ByteSize::_CS8: res= "CS8"; break;
    }
    return std::string(res);
}

void ParamsRS232::setBaudRate(string _speed)
{
    auto it = baudeRate.find(_speed);

    if(it != baudeRate.end())
    {
        speed = baudeRate[_speed];
    }
    else
    {
        std::cout << "Error find baude rate " << _speed << " set default 9600" << std::endl;
        speed   = baudeRate["9600"];
    }
}


bool ParamsRS232::fromJSON(const rapidjson::Value &doc)
{
    bool result = false;
    const char* members[] = { "DevPath", "Speed", "Parity", "ByteSize", "WakeUP9Bit"};

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
            //uint64_t id = doc["DevPath"].GetUint64();
            setDevPath(doc[members[0]].GetString());
            setBaudRate(doc[members[1]].GetString());

            string str_parity(doc[members[2]].GetString());

            if(str_parity == "Even")
            {
                parity = Parity::Even;
            }
            else
                if(str_parity == "Odd")
                {
                    parity = Parity::Odd;
                }

            string str_bs(doc[members[3]].GetString());
            if(str_bs == "CS8")
            {
                byteSize = ByteSize::_CS8;
            }
            else
                if(str_bs == "CS7")
                {
                    byteSize = ByteSize::_CS7;
                }
                else
                    if(str_bs == "CS6")
                    {
                        byteSize = ByteSize::_CS6;
                    }
                    else
                        if(str_bs == "CS5")
                        {
                            byteSize = ByteSize::_CS5;
                        }


            if(std::string(doc[members[4]].GetString()) == "True")
                Is9thbit = true;
            else
                Is9thbit= false;

            result = true;
        }
    }
    return result;
}

void ParamsRS232::toJSON(rapidjson::Document &doc)
{
    auto& allocator = doc.GetAllocator();

    rapidjson::Value val;
    rapidjson::Value obj(rapidjson::kObjectType);

    val.SetString(getDevPath().c_str(), allocator);
    obj.AddMember("DevPath", val, allocator);

    val.SetString(getBaudRateString().c_str(), allocator);
    obj.AddMember("Speed", val, allocator);


    string str_parity("None");
    if(parity == Parity::Odd)
    {
        str_parity = "Odd";
    }
    else
        if(parity == Parity::Even)
        {
            str_parity = "Even";
        }

    val.SetString(str_parity.c_str(), allocator);
    obj.AddMember("Parity", val, allocator);

    val.SetString(getByteSizeString().c_str(), allocator);
    obj.AddMember("ByteSize", val, allocator);

    val.SetString(Is9thbit ? "True":"False", allocator);
    obj.AddMember("WakeUP9Bit", val, allocator);

    doc.AddMember("Params", obj, allocator);
}
