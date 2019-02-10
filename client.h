//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <fstream>
#include <vector>

#include "workerrs.h"
#include "paramsrs.h"

class Client: public WorkerRS
{

public:
    //Client(string devPath, string fileName);
    Client(ParamsRS _params, string fileName);

    ~Client();

protected:
    void run_func();

private:
    void openFile();

    //ParamsRS params;

    ifstream fileStream;
    string fileName;

};

#endif // CLIENT_H
