#ifndef IWORKER
#define IWORKER

#include "iinterface.h"

class IWorker
{    
protected:
    void setInterface(std::shared_ptr<IInterface> i) { interface = i; }

    std::shared_ptr<IInterface> getInterface() { return interface; }

private:
    std::shared_ptr<IInterface> interface;
};

#endif // IWORKER

