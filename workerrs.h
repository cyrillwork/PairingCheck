#ifndef WORKERRS_H
#define WORKERRS_H

#include <thread>
#include <string>
#include <fstream>

#include "interface.h"
#include "const.h"

class WorkerRS
{

public:
    WorkerRS(string devPath);
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

    std::thread run_thread;
    std::string devPath;
};

#endif // WORKERRS_H
