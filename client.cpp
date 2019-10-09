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

#ifdef ECHO_RESPONSE
        { // read
            int count1 = 0;
            std::cout << std::hex;
            do {
                res = getInterface()->read(buff, BUFF_SIZE, DELAY_MSEC*1000);
                if(res > 0)
                {
                    for(int iii = 0; iii < res; ++iii)
                    {
                        std::cout << " " << buff[iii];
                    }
                }

                count1 += res;

                if(count1 == res_send)
                {
                    break;
                }

            } while ( res != 0 );

            std::cout << std::endl;
            std::cout << std::dec;
        }
#endif

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

