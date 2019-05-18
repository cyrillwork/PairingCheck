#include "paramsrs.h"


ParamsRS::ParamsRS(): IParams("/dev/ttyS0")
{
    //set default state
    parity  = Parity::None;
    speed   = baudeRate["9600"];
    byteSize = ByteSize::_CS8;
}

ParamsRS::ParamsRS(ParamsRS &params):
    IParams(params.getDevPath()),
    parity(params.getParity()),
    speed(params.getBaudRate()),
    byteSize(params.getByteSize()),
    Is9thbit(params.Is9thbit)
{

}

ParamsRS::ParamsRS(string dev, Parity parity, int speed, ByteSize byteSize):
    IParams(dev)
{
    parity      = parity;
    speed       = speed;
    byteSize    = byteSize;
}

void ParamsRS::setBaudRate(string _speed)
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

bool ParamsRS::fromJSON(const rapidjson::Value &doc)
{
    bool result = false;

    if(doc.IsObject())
    {
        bool isOK = true;
        const char* members[] = { "DevPath", "Speed", "ByteSize", "Parity" };

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
            setDevPath(doc["DevPath"].GetString());

            setBaudRate(doc["Speed"].GetString());

            string str_parity(doc["Parity"].GetString());

            if(str_parity == "Even")
            {
                parity = Parity::Even;
            }
            else
                if(str_parity == "Odd")
                {
                    parity = Parity::Odd;
                }

            result = true;
        }
    }


    return result;

}
