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
    cout << "Server mode: PairingRS -server -devpath port" << endl;
    cout << "Client mode: PairingRS -client filename -devpath port" << endl;
}

int main(int argc, char *argv[])
{
    char fileName[128];
    int Mode = NONE;

    ParamsRS params;

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

    };

        const char *optString = "c:d:c?";

        while(true)
        {
            int c;

            int option_index = 0;

            c = getopt_long(argc, argv, optString, long_options, &option_index);

            if(c == -1)
            {
                break;
            }

            std::cout << "getopt c=" << (char)c << std::endl;

            switch(c)
            {

            case 's':
                Mode = SERVER;
                //printf("set option show time\n");
                break;

            case 'c':
                Mode = CLIENT;
                //printf("set option link as file\n");
                strcpy(fileName, optarg);
                break;

            case 'd':
                params.setDevPath(optarg);
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
                cout << "params.getDevPath() = " << params.getDevPath() << endl;

                Client client(params, fileName);

                getchar();
            }
            catch (WorkerRS::WorkerRSEx ex)
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
                cout << "params.getDevPath() = " << params.getDevPath() << endl;
                Server server(params);

                //Server server(argv[optind]);

                getchar();
            }
            catch (WorkerRS::WorkerRSEx ex)
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
