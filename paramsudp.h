#ifndef UDPPARAMS_H
#define UDPPARAMS_H

#include "iparams.h"

class ParamsUDP : public IParams
{
public:
    ParamsUDP():IParams("127.0.0.1") {}
    ParamsUDP(std::string dev);
    const std::string getName() noexcept override { return std::string("UDP"); }
};

#endif // UDPPARAMS_H
