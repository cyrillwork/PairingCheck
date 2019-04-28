#include "paramsrs.h"


ParamsRS::ParamsRS()
{
    //set default state
    devPath = "/dev/ttyS0";
    parity  = Parity::None;
    speed   = baudeRate["9600"];
    byteSize = ByteSize::_CS8;
}

ParamsRS::ParamsRS(ParamsRS &params):
    devPath(params.getDevPath()),
    parity(params.getParity()),
    speed(params.getBaudRate()),
    byteSize(params.getByteSize()),
    Is9thbit(params.Is9thbit)
{

}

ParamsRS::ParamsRS(string dev, Parity parity, int speed, ByteSize byteSize)
{
    devPath     = dev;
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
