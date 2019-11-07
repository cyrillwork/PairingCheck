#include "linuxserial.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>

LinuxSerial::LinuxSerial()
{
}

LinuxSerial::~LinuxSerial()
{
}

int LinuxSerial::open(const char*pathname, int flags)
{
    return fd = ::open(pathname, flags);
}

int LinuxSerial::close()
{
    return (fd > 0) ? (::close(fd)) : 0;
}

size_t LinuxSerial::read(char* buff, size_t len)
{	
    return ::read(fd, buff, len);
}

size_t LinuxSerial::write(const char*buff, size_t len)
{
    return ::write(fd, buff, len);
}

int LinuxSerial::select(size_t timeout)
{
    struct timeval tv;
    fd_set fds;
    int resfds;
    FD_ZERO (&fds);
    FD_SET (fd, &fds);

    tv.tv_sec = (size_t)(timeout / 1000000);
    tv.tv_usec = timeout - tv.tv_sec*1000000;

    resfds = ::select(fd + 1, &fds, NULL, NULL, &tv);

    return (resfds <= 0) ? 0 : 1;
}

int LinuxSerial::tcsetattr(int optional_actions, const termios* termios_p)
{
    ::memcpy(&(this->termios_p), termios_p, sizeof(termios));

    return ::tcsetattr(fd, optional_actions, &(this->termios_p));
}

int LinuxSerial::cfsetispeed(speed_t speed)
{
    return ::cfsetispeed(&termios_p, speed);
}

int LinuxSerial::cfsetospeed(speed_t speed)
{
    return ::cfsetospeed(&termios_p, speed);
}

PtrSerial getSerial()
{
#ifdef _WIN32
    return make_shared<WinSerial>();
#else
    return std::make_shared<LinuxSerial>();
#endif
}
