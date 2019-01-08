//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#include "rs_interface.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>

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

RSInterface::~RSInterface()
{
}

bool RSInterface::open()
{
    cout << "RSInterface::open() " << devPath << endl;
    _channelId = ::open(devPath.c_str(), O_RDWR | O_NONBLOCK /*O_RDWR | O_NOCTTY | O_NONBLOCK*/);

    if (_channelId < 0)
    {
        cout << "Can't open device" << devPath << endl;
        perror(devPath.c_str());
        return false;
    }
    struct termios newtio0;

    memset (&newtio0, 0, sizeof (newtio0));
/*
    newtio0.c_cflag = _baudRate[BAUDRATE] | _byteSize[BYTESIZE] | CLOCAL | CREAD | PARENB;

	newtio0.c_cflag &= ~CRTSCTS;
	newtio0.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	newtio0.c_oflag &= ~OPOST;

	//| _parity[PARITY];

    newtio0.c_oflag = 0;
    newtio0.c_lflag = 0;
    newtio0.c_cc[VTIME] = 0;    // inter-character timer unused
    newtio0.c_cc[VMIN]  = 1;    // blocking read until  chars received
*/

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

/*
	newtio0.c_iflag = IGNBRK;

	newtio0.c_iflag &= (~IGNPAR);
	newtio0.c_iflag &= ~(INPCK | ISTRIP);
	newtio0.c_iflag &= ~(IXON | IXOFF | IXANY);
	newtio0.c_cflag = CREAD | CLOCAL;
	//newtio0.c_cflag |= PARENB;
	newtio0.c_cflag &= ~CSTOPB;
	newtio0.c_cflag &= ~CSIZE;
	newtio0.c_cflag |= CS8;
	newtio0.c_cflag &= ~CRTSCTS;


    newtio0.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    newtio0.c_oflag &= ~OPOST;

    newtio0.c_cc[VMIN] = 0;
    newtio0.c_cc[VTIME]= 0;

*/



    cfsetospeed(&newtio0, _baudRate[BAUDRATE] );
    cfsetispeed(&newtio0, _baudRate[BAUDRATE] );

    tcflush (_channelId, TCIFLUSH);
    tcsetattr (_channelId, TCSANOW, &newtio0);

	// Set receive with space parity
	newtio0.c_cflag |= PARENB;
	newtio0.c_cflag |= CMSPAR;
	newtio0.c_cflag &= ~PARODD;
	tcsetattr(_channelId, TCSANOW, &newtio0);

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
    return ::write(_channelId, data, size);
}
