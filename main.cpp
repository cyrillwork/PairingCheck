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
    cout << "Server mode: PairingCheck --server --config filename.json " << endl;
    cout << "Client mode: PairingCheck --client filename --config filename.json" << endl;
    cout << "Default params: speed 9600, size 8bit, parity none, stop bite 1" << endl;

    cout << "For generate config file: " << endl;
    cout << "PairingCheck --generate type[RS232|UDP]" << endl;
}

TypeInterface interfaceFactory(TypeParams params)
{
    TypeInterface interface = nullptr;

    switch (params->getType())
    {
        case TypeParam::RS232:
        {//set up RS-interface
            interface = make_shared<RSInterface>(params);
        }
        break;

        case TypeParam::UDP:
        {
            interface = make_shared<UDPInterface>(params);
        }
        break;

        case TypeParam::None:
            cout << "Error get param, interfaceFactory!!!" << endl;
        break;
    }

    return interface;
}

int main(int argc, char *argv[])
{
    std::string fileName;
    int Mode = NONE;

    TypeParams params = nullptr;

    if(argc < 3)
    {
        printErrorMessage();
    }
    else
    {
        static struct option long_options[] =
        {
        {"client",      required_argument,      nullptr,  'c'},
        {"server",      no_argument,            nullptr,  's'},
        {"config",      required_argument,      nullptr,  'f'},
        {"devpath",     required_argument,      nullptr,  'd'},
        {"type",        required_argument,      nullptr,  't'},
        {"speed",       required_argument,      nullptr,  'b'},
        {"generate",    required_argument,      nullptr,  'g'},
        {"wakeupbit",   no_argument,            nullptr,  'w'},

    };

        const char *optString = "c:d:b:sw?";

        while(true)
        {
            int c;
            int option_index = 0;

            c = getopt_long_only(argc, argv, optString, long_options, &option_index);


            if(c == -1)
            {
                break;
            }

            switch(c)
            {
                case 's':
                    Mode = SERVER;
                break;

                case 'c':
                    Mode = CLIENT;
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

                case 'g':
                {
                    TypeParam type = IParams::getTypeParam(optarg);
                    if(type != TypeParam::None)
                    {
                        ConfigFileParser::generateJSON(type);
                    }
                    else
                    {
                        cout << "Error generate configfile. Wrong type " << optarg << endl;
                        printErrorMessage();
                    }
                    exit(0);
                }

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
