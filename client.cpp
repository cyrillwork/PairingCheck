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
    //std::cout << "Close client " << std::endl;
    fileStream.close();
    //std::cout << "~Client " << std::endl;
}

void Client::run_func()
{
    if(!isOpened)
    {
        return;
    }

    char buff[BUFF_SIZE];
    fileStream.read(buff, BUFF_SIZE);
    int res = fileStream.gcount();

    //std::cout << "slice bytes res=" <<res << std::endl;

    if(res > 0)
    {
        int res_send = getInterface()->write(buff, res);
        count_send += res_send;

        std::cout << "Send " << count_send << " bytes" << std::endl;
    }
    else
    {
        std::cout << "All data send "<< count_send <<", file size " << file_size << std::endl;
        std::cout << "press Enter..." << std::endl;
        isRun = false;
    }
}

void Client::openFile()
{
    fileStream.open(fileName, std::ios::binary);

    if(!fileStream.is_open())
    {
        isRun = false;
        throw WorkerEx("File do not opened " + fileName);
    }

    // get length of file:
    fileStream.seekg (0, fileStream.end);
    file_size = fileStream.tellg();
    fileStream.seekg (0, fileStream.beg);

    //std::cout << "file_size=" << file_size << std::endl;
    isOpened = true;
}

