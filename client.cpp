//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#include "client.h"
/*
Client::Client(string devPath, string fileName): WorkerRS(devPath)
{
    this->fileName = fileName;

    openFile();
}
*/

Client::Client(ParamsRS _params, string fileName):
    WorkerRS(_params)

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
        int res_send = interface()->write(buff, res);
        count_send += res_send;
        cout << "Send " << count_send << " bytes" << endl;
    }
    else
    {
        cout << "All data send "<< count_send <<", prees Enter" << endl;
        isRun = false;
    }
}

void Client::openFile()
{
    fileStream.open(fileName, ios::binary);

    if(!fileStream)
    {
        isRun = false;
        throw WorkerRSEx("File do not opened " + fileName);
    }
/*
    while (!fileStream.eof())
    {
        char buff[BUFF_SIZE];
        fileStream.read(buff, BUFF_SIZE);
        int res = fileStream.gcount();
        for(int iii = 0; iii<res; iii++)
        {
            arrayData.push_back(buff[iii]);
        }
    }
    cout << "Read file size = " << arrayData.size() << endl;
*/
}

