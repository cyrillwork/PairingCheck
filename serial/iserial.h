#ifndef ISERIAL_H
#define ISERIAL_H

#include <iostream>

#ifdef _WIN32
    #define NOMINMAX //иначе API windows определит макросы min и max, конфликтующие с std::max и std::min в vector
    #include <windows.h>
    #undef interface

    #include "win_serial.h"

    using namespace win_serial;
#else
    #include <termios.h>
#endif

class ISerial
{
public:
    virtual ~ISerial() = default;
    virtual int open (const char *pathname, int flags) = 0;
    virtual int close (int fd) = 0;
    virtual size_t read(char* buff, size_t len) = 0;
    virtual size_t write(const char* buff, size_t len) = 0;
    virtual int tcsetattr(int optional_actions, const termios* termios_p) = 0;

    virtual int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout) = 0;

protected:
    int fd{0};
};

#endif
