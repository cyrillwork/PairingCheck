//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#ifndef WORKERRS_H
#define WORKERRS_H

#include <thread>
#include <string>
#include <fstream>

//#include "interface.h"

#include "iworker.h"
#include "rsinterface.h"
#include "udpinterface.h"
#include "const.h"
#include "paramsrs.h"

class Worker: public IWorker
{
public:
    Worker(TypeParams _params);

    Worker(const Worker &w) = delete;

    ~Worker();

    void startThread() { isRun = true; }
    void stopThread() { isRun = false; }

    class WorkerEx
    {
    public:
        string message;
        WorkerEx(string message) { this->message = message; }
    };

protected:

    bool isRun;

private:
    void run();
    TypeParams params;
    std::unique_ptr <std::thread> run_thread;
};

#endif // WORKERRS_H
