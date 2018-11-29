#include <iostream>
#include <getopt.h>

#include "client.h"
#include "server.h"

using namespace std;

enum
{
    NONE = 0,   // режим не установлен
    CLIENT,     // клиент
    SERVER      // сервер
} Prog_Mode;

void printErrorMessage()
{
    cout << "Error. Usage: " << endl;
    cout << "Server mode: PairingRS -s port" << endl;
    cout << "Client mode: PairingRS -c filename" << endl;
    cout << "Default client port /dev/ttyS0" << endl;
}

int main(int argc, char *argv[])
{
    int Mode = NONE;

    //cout << "Hello, server " << Server::getFileName() << endl;

    if(argc != 3)
    {
        printErrorMessage();
    }
    else
    {
        while(true)
        {
            int c;
            static struct option long_options[] =
            {
                {"c", 0, 0, 0},
                {"s", 0, 0, 0},
            };

            int option_index = 0;
            c = getopt_long(argc, argv, "c s", long_options, &option_index);

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
                break;
            }
        }

        switch(Mode)
        {
            case CLIENT:
            {
                try
                {
                    cout << "create client" << endl;
                    Client client(argv[optind]);
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
                    Server server(argv[optind]);
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
