//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#include <iostream>
#include <getopt.h>

#include "client.h"
#include "server.h"
#include "paramsrs.h"

using namespace std;

enum
{
    NONE = 0,   // режим не установлен
    CLIENT,     // клиент
    SERVER      // сервер
};

void printErrorMessage()
{
    cout << "Error. Usage: " << endl;
    cout << "Server mode: PairingRS --server --devpath port [--wakeupbit] [--speed buadrate]" << endl;
    cout << "Client mode: PairingRS --client filename --devpath port [--wakeupbit] [--speed buadrate]" << endl;
    cout << "Default params: speed 9600, size 8bit, parity none, stop bite 1" << endl;
}

int main(int argc, char *argv[])
{
    std::string fileName;
    int Mode = NONE;

    TypeParams params = make_unique<ParamsRS>();

    //cout << "Hello, server " << Server::getFileName() << endl;

    if(argc < 3)
    {
        printErrorMessage();
    }
    else
    {
        static struct option long_options[] =
        {
        {"client",      required_argument,      0,  'c'},
        {"server",      no_argument,            0,  's'},
        {"devpath",     required_argument,      0,  'd'},
        {"speed",       required_argument,      0,  'b'},
        {"wakeupbit",   no_argument,            0,  'w'},

    };

        const char *optString = "c:d:b:sw?";

        while(true)
        {
            int c;

            int option_index = 0;

            c = getopt_long(argc, argv, optString, long_options, &option_index);

            if(c == -1)
            {
                break;
            }

            switch(c)
            {

            case 's':
                Mode = SERVER;
                //printf("set option show time\n");
                break;

            case 'c':
                Mode = CLIENT;
                //printf("set option link as file\n");
                fileName = optarg;
                break;

            case 'd':
                params->setDevPath(optarg);
                break;

            case 'b':
            {
                std::cout << "set baudrate" << optarg << std::endl;
                params->setBaudRate(optarg);
            }
            break;

            case 'w':
            {
                std::cout << "set 9th bit (wakeup bit)" << std::endl;
                params->set9thBit(true);
            }
            break;

            case '?':
            {
                printErrorMessage();
                return 0;
            }

            }
        }



        switch(Mode)
        {
        case CLIENT:
        {
            try
            {
                cout << "create client fileName=" << fileName << endl;
                cout << "params->getDevPath() = " << params->getDevPath() << endl;

                Client client(std::move(params), fileName);

                getchar();
            }
            catch (Worker::WorkerEx ex)
            {
                cout << "Exception client: " << ex.message << endl;
                return 0;
            }
        }
            break;
        case SERVER:
        {
            try
            {
                cout << "create server" << endl;
                cout << "params->getDevPath() = " << params->getDevPath() << endl;
                Server server(std::move(params));

                //Server server(argv[optind]);

                getchar();
            }
            catch (Worker::WorkerEx ex)
            {
                cout << "Exception server: " << ex.message << endl;
                return 0;
            }
        }
            break;
        default:
        {
            printErrorMessage();
        }
        }


    }
    return 0;
}
