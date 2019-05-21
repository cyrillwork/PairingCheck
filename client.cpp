//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#include "client.h"


Client::Client(TypeParams _params, TypeInterface interface, string fileName):
    Worker(_params, interface)
{
    this->fileName = fileName;
    openFile();
}

Client::~Client()
{
    fileStream.close();
}

void Client::run_func()
{
    static int count_send = 0;

    char buff[BUFF_SIZE];
    fileStream.read(buff, BUFF_SIZE);
    int res = fileStream.gcount();

    if(res > 0)
    {
        int res_send = getInterface()->write(buff, res);
        count_send += res_send;
        std::cout << "Send " << count_send << " bytes" << std::endl;
    }
    else
    {
        std::cout << "All data send "<< count_send <<", prees Enter" << std::endl;
        isRun = false;
    }
}

void Client::openFile()
{
    fileStream.open(fileName, std::ios::binary);

    if(!fileStream)
    {
        isRun = false;
        throw WorkerEx("File do not opened " + fileName);
    }
}

