#include "paramsrs.h"


ParamsRS::ParamsRS()
{
    //set default state
    this->devPath = "/dev/ttyS0";
    this->parity = Parity::None;
    this->speed = this->baudeRate["9600"];
    this->byteSize = ByteSize::_CS8;
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
    this->devPath = dev;
    this->parity = parity;
    this->speed = speed;
    this->byteSize = byteSize;
}
