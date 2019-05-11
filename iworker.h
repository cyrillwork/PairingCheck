#ifndef IWORKER
#define IWORKER

#include "iinterface.h"

class IWorker
{    
protected:

    virtual ~IWorker() = default;

    void virtual run_func() = 0;

    void setInterface(std::shared_ptr<IInterface> i) { interface = i; }

    std::shared_ptr<IInterface> getInterface() { return interface; }

private:
    std::shared_ptr<IInterface> interface;
};

#endif // IWORKER

