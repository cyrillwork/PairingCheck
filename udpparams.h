#ifndef UDPPARAMS_H
#define UDPPARAMS_H

#include "iparams.h"

class UDPParams : public IParams
{
public:
    UDPParams(std::string dev);
    const std::string getName() noexcept override { return std::string("Params UDP"); }
};

#endif // UDPPARAMS_H
