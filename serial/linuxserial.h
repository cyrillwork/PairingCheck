#pragma once

#ifndef LINUXSERIAL_H
#define LINUXSERIAL_H

#include "iserial.h"
#include <memory>

class LinuxSerial: public ISerial
{

public:
    LinuxSerial();

    virtual ~LinuxSerial() override;

    virtual int open(const char *pathname, int flags) override;

    virtual int close() override;

    virtual size_t read(char* buff, size_t len) override;

    virtual size_t write(const char* buff, size_t len) override;

    virtual int select(size_t timeout) override;

    virtual int tcsetattr(int optional_actions, const termios* termios_p) override;

    virtual int cfsetispeed(speed_t speed) override;

    virtual int cfsetospeed(speed_t speed) override;

private:

};


PtrSerial getSerial();


#endif // LINUXSERIAL_H
