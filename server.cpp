//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#include <ctime>
#include <fstream>

#include "server.h"

int Server::countFiles = 0;

Server::Server(TypeParams _params, TypeInterface interface):
    Worker(_params, interface)
{
    isGetData = false;

    if(_params->getName() == "UDP")
    {
        interface->bind();
    }
}

string Server::getFileName()
{
    char buff[128];
    time_t t = time(nullptr);   // get time now

    buff[0] = 0x0;
    countFiles++;

    strftime(buff, 128, "%X", localtime( &t ));

    return string(buff) + "_" + std::to_string(countFiles) + ".hex";
}

void Server::run_func()
{
    char buff[BUFF_SIZE];

    int res = getInterface()->read(buff, BUFF_SIZE, DELAY_MSEC*1000);

    cout << "server get res="<< res << endl;

    if(res > 0)
    {
        if(!isGetData)
        {
            cout << "Start get data" << endl;
        }
        isGetData = true;

        for(int iii = 0; iii<res; iii++)
        {
            ArrayData.push_back(buff[iii]);
        }
    }
    else
    {
        if(isGetData)
        {
            //Write data to file
            string fileName = getFileName();
            ofstream file(fileName, ios::binary|ios::trunc);
            file.write(ArrayData.data(), ArrayData.size());
            file.close();
            cout << "Write file " << fileName << endl;

            //Clear some data
            isGetData = false;
            ArrayData.clear();
        }
    }

}

