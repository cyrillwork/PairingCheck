//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <fstream>
#include <vector>

#include "workerrs.h"
#include "paramsrs.h"

class Client: public Worker
{
public:
    Client(TypeParams _params, TypeInterface interface, string fileName);
    ~Client();

protected:
    void run_func() override;

private:
    void openFile();

    std::ifstream fileStream;
    string fileName;
};

#endif // CLIENT_H
