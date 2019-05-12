//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#include "workerrs.h"


Worker::Worker(TypeParams _params, TypeInterface interface):
    params(_params)
{
    //setup connection interface
    setInterface(interface);

    auto dev = getInterface()->getDevName();

    std::cout << "Worker devPath=" << dev << std::endl;

    if(!getInterface()->open())
    {
        throw WorkerEx("Error open dev=" + dev);
    }

    isRun = true;

    run_thread = make_unique<std::thread>(&Worker::run, this);
}

Worker::~Worker()
{
    isRun = false;
    run_thread->join();

    getInterface()->close();
}

void Worker::run()
{

    while(isRun)
    {
        run_func();
        std::this_thread::sleep_for(chrono::milliseconds(DELAY_MSEC));
    }
}


