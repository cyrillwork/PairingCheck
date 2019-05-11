//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#ifndef WORKERRS_H
#define WORKERRS_H

#include <thread>
#include <string>
#include <fstream>

//#include "interface.h"

#include "iworker.h"
#include "rsinterface.h"
#include "const.h"
#include "paramsrs.h"

class WorkerRS: public IWorker
{
public:
    WorkerRS(TypeParams _params);

    WorkerRS(const WorkerRS &w) = delete;
    WorkerRS operator= (const WorkerRS &w) = delete;

    ~WorkerRS();

    void startThread() { isRun = true; }
    void stopThread() { isRun = false; }

    class WorkerRSEx
    {
    public:
        string message;
        WorkerRSEx(string message) { this->message = message; }
    };

protected:
    void virtual run_func();

    bool isRun;

private:
    void run();
    TypeParams params;
    std::unique_ptr <std::thread> run_thread;
};

#endif // WORKERRS_H
