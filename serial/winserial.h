#ifndef WINSERIAL_H
#define WINSERIAL_H

#include "iserial.h"

namespace win_serial
{

class WinSerial: public ISerial
{
public:

    WinSerial();
    virtual ~WinSerial() override;

    bool IsOK() const;

    virtual int open(const char *pathname, int flags) override;
    virtual int close(int fd) override;

    virtual size_t read(char* buff, size_t len) override;
    virtual size_t write(const char* buff, size_t len) override;

    virtual int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout) override;

    virtual int tcsetattr(int optional_actions, const termios* termios_p) override;

private:
    HANDLE m_Handle;
    int TIMEOUT = 1000;

    DCB SerialParams = {}; //Initializing DCB structure
};

}

#endif // WINSERIAL_H
