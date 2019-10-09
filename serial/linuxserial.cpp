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

size_t LinuxSerial::read(char* buff, size_t len, size_t timeout)
{
	if(this->select(timeout * 1000))
		return ::read(fd, buff, len);
	else
		return 0;
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

int LinuxSerial::tcsetattr(int /*optional_actions*/, const termios*/*termios_p*/)
{

}
