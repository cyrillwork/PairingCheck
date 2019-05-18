//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#include <iostream>
#include <getopt.h>

#include "client.h"
#include "server.h"
#include "configfileparser.h"

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
    cout << "Server mode: PairingCheck --server --configfile.json " << endl;
    cout << "Client mode: PairingCheck --client filename --config configfile.json" << endl;
    cout << "Default params: speed 9600, size 8bit, parity none, stop bite 1" << endl;
}

TypeInterface interfaceFactory(TypeParams params)
{
    TypeInterface interface = nullptr;

    //set up RS-interface
    if(params->getName() == "RS232")
    {
        interface = make_shared<RSInterface>(params);
    }
    else
        if(params->getName() == "UDP")
        {
            interface = make_shared<UDPInterface>(params);
        }

    return interface;
}

int main(int argc, char *argv[])
{
    std::string fileName;
    int Mode = NONE;

    TypeParams params = nullptr;

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
        {"configfile",  required_argument,      0,  'f'},
        {"devpath",     required_argument,      0,  'd'},
        {"type",        required_argument,      0,  't'},
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

                case 'f':
                {
                    ConfigFileParser parser(optarg);
                    if(!parser.Init())
                    {
                        cout << "Error parse file " << optarg << endl;
                        printErrorMessage();
                        exit(0);
                    }
                    params = parser.getParams();

                }
                break;

                case '?':
                {
                    printErrorMessage();
                    return 0;
                }

            }
        }

        TypeInterface interface = interfaceFactory(params);

        if(!interface)
        {
            cout << "Unkown interface type" << endl;
            return 0;
        }

        if(!params)
        {
            cout << "Unkown config data file" << endl;
            return 0;
        }


        switch(Mode)
        {
            case CLIENT:
            {
                try
                {
                    cout << "create client fileName=" << fileName << endl;
                    cout << "params->getDevPath() = " << params->getDevPath() << endl;

                    Client client(params, interface, fileName);

                    getchar();
                }
                catch (Worker::WorkerEx ex)
                {
                    cout << "Exception client: " << ex.message << endl;
                }
            }
            break;
            case SERVER:
            {
                try
                {
                    cout << "create server" << endl;
                    cout << "params->getDevPath() = " << params->getDevPath() << endl;
                    Server server(params, interface);

                    //Server server(argv[optind]);

                    getchar();
                }
                catch (Worker::WorkerEx ex)
                {
                    cout << "Exception server: " << ex.message << endl;
                }
            }
            break;
            default:
            {
                printErrorMessage();
            }
        }
    }

    if(params)
    {
        delete params;
    }

    return 0;
}
