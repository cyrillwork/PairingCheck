//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#include "rs_interface.h"

/*
RSInterface::RSInterface(string devPath): _channelId(-1)
{
    this->devPath = devPath;

    int array1[] = {50, 75,  110,   134,  150,  200,  300,  600,  1200,  1800,  2400,  4800,  9600,  19200,  38400,  57600,  115200, 230400};
    int array2[] = {B50, B75, B110, B134, B150, B200, B300, B600, B1200, B1800, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400};

    for(unsigned int iii=0; iii < (sizeof(array1)/sizeof(int)); iii++)
    {
        _baudRate[array1[iii]] = array2[iii];
    }

    _parity[string("None")] = 0;
    _parity[string("Odd")] = PARENB | PARODD;
    _parity[string("Even")] = PARENB;

    _byteSize[5] = CS5;
    _byteSize[6] = CS6;
    _byteSize[7] = CS7;
    _byteSize[8] = CS8;
}
*/

RSInterface::RSInterface(ParamsRS _params):
    params(_params),
    _channelId(-1)
{
    cout << "constructor RSInterface devPath=" << params.getDevPath() << endl;
}

RSInterface::~RSInterface()
{
}

bool RSInterface::open()
{
    cout << "RSInterface::open() " << params.getDevPath() << endl;

    _channelId = ::open(params.getDevPath().c_str(), O_RDWR | O_NONBLOCK /*O_RDWR | O_NOCTTY | O_NONBLOCK*/);

    if (_channelId < 0)
    {
        cout << "Can't open device" << params.getDevPath() << endl;
        perror(params.getDevPath().c_str());
        return false;
    }


    memset (&newtio0, 0, sizeof (newtio0));


    if(params.get9thBit())
    {
        // 9th bit
        newtio0.c_iflag = IGNBRK;

        newtio0.c_iflag &= ~IGNPAR;
        newtio0.c_iflag &= ~ISTRIP;
        newtio0.c_iflag |= INPCK;
        newtio0.c_iflag |= PARMRK; // Mark all bytes received with 9th bit set by "ff 0"
        newtio0.c_cflag |= CMSPAR;
        newtio0.c_cflag &= ~PARODD;	// normal state - space parity

        newtio0.c_iflag &= ~(IXON | IXOFF | IXANY);
        newtio0.c_cflag = CREAD | CLOCAL;
        newtio0.c_cflag |= PARENB;
        newtio0.c_cflag &= ~CSTOPB;
        newtio0.c_cflag &= ~CSIZE;
        newtio0.c_cflag |= CS8;
        newtio0.c_cflag &= ~CRTSCTS;
        newtio0.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        newtio0.c_oflag &= ~OPOST;
        newtio0.c_cc[VMIN] = 0;
        newtio0.c_cc[VTIME]= 0;

        cfsetospeed(&newtio0, params.getBaudRate() );
        cfsetispeed(&newtio0, params.getBaudRate() );

        tcflush (_channelId, TCIFLUSH);
        tcsetattr (_channelId, TCSANOW, &newtio0);

        // Set receive with space parity
        newtio0.c_cflag |= PARENB;
        newtio0.c_cflag |= CMSPAR;
        newtio0.c_cflag &= ~PARODD;
        tcsetattr(_channelId, TCSANOW, &newtio0);

    }
    else
    {
        newtio0.c_cflag = params.getBaudRate() | params.getByteSize() | CLOCAL | CREAD | (int)params.getParity();

        newtio0.c_cflag &= ~CRTSCTS;
        newtio0.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        newtio0.c_oflag &= ~OPOST;

        newtio0.c_oflag = 0;
        newtio0.c_lflag = 0;
        newtio0.c_cc[VTIME] = 0;    // inter-character timer unused
        newtio0.c_cc[VMIN]  = 1;    // blocking read until  chars received

        tcflush (_channelId, TCIFLUSH);
        tcsetattr (_channelId, TCSANOW, &newtio0);
    }

    return true;
}

bool RSInterface::close()
{
    return true;
}

int RSInterface::read(char *data, int size, int timeout)
{
    struct timeval tv;
    fd_set fds;
    int resfds;

    FD_ZERO (&fds);
    FD_SET (_channelId, &fds);
    tv.tv_sec = (int)(timeout / 1000000);
    tv.tv_usec = timeout - tv.tv_sec*1000000;

    resfds = select(_channelId + 1, &fds, NULL, NULL, &tv);
    if(resfds <= 0)
    {
        //cout << "Read timeout" << endl;
        return 0;
    }

    return ::read(_channelId, data, size);
}

int RSInterface::write(const char *data, int size)
{
    if(params.get9thBit())
    {
        for(int iii = 0; iii<size; iii++)
        {
            if(putCharWakeup(data[iii]) == -1)
            {
                return -1;
            }
        }
        return size;
    }
    else
    {
        return ::write(_channelId, data, size);
    }
}

/******************************************************************************
** SRL_PutCharWakeup
**
** Description:	put char with wakeup bit
** Input:		symbol - characted to be sent
** Return:		 1 - OK
**               0 - nothing wrote
**				-1 - ERROR
******************************************************************************/
int RSInterface::putCharWakeup(unsigned char symbol)
{
    int				i, rc;
    unsigned char	tmp, nine;

    tmp  = symbol;
    nine = 0;

    for(i=0;i<8;i++)
    {
        nine ^= (tmp & 0x01);
        tmp = tmp >> 1;
    }
    if (nine)
        newtio0.c_cflag = (newtio0.c_cflag | PARENB) & (~PARODD);
    else
        newtio0.c_cflag =  newtio0.c_cflag | PARENB | PARODD;

    tcdrain(_channelId);
    if (tcsetattr(_channelId, TCSADRAIN , &newtio0) == -1)
        return -1;

    rc = ::write(_channelId, &symbol, 1);

    if(!params.get9thBit())
        newtio0.c_cflag = newtio0.c_cflag & (~PARENB) & (~PARODD);

    tcdrain(_channelId);

    //if(params.get9thBit())
    {
        usleep(10000);
        // Set receive with space parity
        newtio0.c_cflag |= PARENB;
        newtio0.c_cflag |= CMSPAR;
        newtio0.c_cflag &= ~PARODD;
    }

    tcsetattr(_channelId, TCSADRAIN, &newtio0);

    return rc;
}

