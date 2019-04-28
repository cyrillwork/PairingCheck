//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#ifndef WORKERRS_H
#define WORKERRS_H

#include <thread>
#include <string>
#include <fstream>

#include "interface.h"
#include "const.h"
#include "paramsrs.h"

class WorkerRS
{
public:
    WorkerRS(ParamsRS& _params);
    ~WorkerRS();

    void stopThread() { isRun = false; }

    class WorkerRSEx
    {
    public:
        string message;
        WorkerRSEx(string message) { this->message = message; }
    };

protected:
    void virtual run_func();

    Interface *interface();

    bool isRun;

private:
    void run();

    ParamsRS& params;
    std::thread run_thread;
    //std::string devPath;
};

#endif // WORKERRS_H
