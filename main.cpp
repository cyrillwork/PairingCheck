//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#include <iostream>
#include <getopt.h>

#include "client.h"
#include "server.h"
#include "paramsrs.h"
#include "paramsudp.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"

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
    cout << "Server mode: PairingCheck --server --type [rs232|udp] --devpath port [--wakeupbit] [--speed buadrate]" << endl;
    cout << "Client mode: PairingCheck --client filename --type [rs232|udp] --devpath port [--wakeupbit] [--speed buadrate]" << endl;
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

TypeParams paramsFactory(const string type)
{
    TypeParams result = nullptr;
    if(type == "UDP")
    {
        result = new ParamsUDP();
    }
    else
    if(type == "RS232")
    {
        result = new ParamsRS();
    }
    return result;
}

int main(int argc, char *argv[])
{
    std::string fileName;
    int Mode = NONE;

    TypeParams params = nullptr;

    //cout << "Hello, server " << Server::getFileName() << endl;
    {
        using namespace rapidjson;
        std::ifstream ifs("config/rs232_server.json");

        if(ifs)
        {
            Document document;
            IStreamWrapper wp(ifs);

            document.ParseStream(wp);

            for(auto it=document.MemberBegin(); it<document.MemberEnd(); ++it)
            {
                std::cout << "Element name=" <<it->name.GetString() << std::endl;
                if(it->value.IsObject())
                {
                    std::cout << "It's Object" << std::endl;
                    const Value &doc = it->value;
                    std::cout << "DevPath = "   << doc["DevPath"].GetString() << std::endl;
                    std::cout << "ByteSize = "  << doc["ByteSize"].GetString() << std::endl;
                    std::cout << "Parity = "    << doc["Parity"].GetString() << std::endl;
                }
            }
        }
        else
        {
            std::cout << "Error. Config file not exist" << std::endl;
        }
    }

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

                case 'd':
                    params->setDevPath(optarg);
                break;

                case 't':
                    cout << "type=" << optarg << endl;
                    params = paramsFactory(optarg);
                    if(params == nullptr)
                    {
                        cout << "Error type=" << optarg << endl;
                        printErrorMessage();
                        exit(0);
                    }
                break;

                case 'b':
                    std::cout << "set baudrate" << optarg << std::endl;
                    {
//                        ParamsRS prs;
//                        IParams *pp = &prs;
//                        ParamsRS *prs2 = dynamic_cast<ParamsRS *>(pp);
//                        prs2->setBaudRate(optarg);

                        TypeParamsRS p = dynamic_cast<TypeParamsRS>(params);
                        p->setBaudRate(optarg);
                    }
                break;

                case 'w':
                {
                    std::cout << "set 9th bit (wakeup bit)" << std::endl;
                    TypeParamsRS p = dynamic_cast<TypeParamsRS>(params);
                    p->set9thBit(true);
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
