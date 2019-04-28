//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#include "workerrs.h"



WorkerRS::WorkerRS(ParamsRS& _params):
    isRun(true),
    params(_params),
    run_thread{&WorkerRS::run, this}
{
    //this->devPath = params.getDevPath();
    std::cout << "WorkerRS devPath=" << params.getDevPath() << std::endl;
    interface();
}

WorkerRS::~WorkerRS()
{
    isRun = false;
    this->run_thread.join();
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

Interface *WorkerRS::interface()
{
    static Interface *instance = 0;

    if(instance == 0)
    {
        instance = new Interface();
        instance->createRSInterface(this->params);

        if(!instance->isOpened())
        {
            isRun = false;
            this->run_thread.join();

            throw WorkerRSEx(string("Error open dev ") + params.getDevPath());
        }

    }

    return instance;
}


