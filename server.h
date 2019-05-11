//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include "workerrs.h"
#include "paramsrs.h"

using namespace std;

class Server: public Worker
{
public:

    Server(TypeParams _params);

    static string getFileName();

protected:
    void run_func() override;

private:
    bool isGetData;
    vector <char> ArrayData;

    static int countFiles;
};



#endif // SERVER_H
