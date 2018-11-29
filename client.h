#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <fstream>
#include <vector>

#include "workerrs.h"

class Client: public WorkerRS
{

public:
    Client(string fileName);
    ~Client();

protected:
    void run_func();

private:
    void openFile();

    ifstream fileStream;
    string fileName;
};

#endif // CLIENT_H
