//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#include "workerrs.h"


WorkerRS::WorkerRS(TypeParams _params):
    params(std::move(_params))
{
    //set up RS-interface
    setInterface(make_shared<RSInterface>(std::move(params)));

    auto dev = getInterface()->getDevName();
    std::cout << "WorkerRS devPath=" << dev << std::endl;

    if(!getInterface()->open())
    {
        throw WorkerRSEx("Error open dev=" + dev);
    }

    isRun = true;

    run_thread = make_unique<std::thread>(&WorkerRS::run, this);
}

WorkerRS::~WorkerRS()
{
    isRun = false;
    run_thread->join();

    getInterface()->close();
}

void WorkerRS::run_func()
{
    cout << "WorkerRS run_func" << endl;
}

void WorkerRS::run()
{

    while(isRun)
    {
        run_func();
        std::this_thread::sleep_for(chrono::milliseconds(DELAY_MSEC));
    }
}


