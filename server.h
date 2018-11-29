#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include "workerrs.h"

using namespace std;

class Server: public WorkerRS
{
public:
    Server(string devPath);

    static string getFileName();

protected:
    void run_func();

private:
    bool isGetData;
    vector <char> ArrayData;
};

#endif // SERVER_H
