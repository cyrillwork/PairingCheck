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
    Client(TypeParams _params, TypeInterface interface, std::string fileName);
    ~Client() override;

protected:
    void run_func() override;

private:
    void openFile();

    std::streampos  count_send = 0;
    std::streampos  file_size = 0;

    std::ifstream fileStream;
    string fileName;

    bool isOpened = false;
};

#endif // CLIENT_H
