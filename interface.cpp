//This is an open source non-commercial project. Dear PVS-Studio, please check it.

#include "interface.h"


void Interface::createRSInterface(const string devPath)
{
    m_interfaceImpl = new RSInterface(devPath);
    open();
}

Interface::~Interface()
{
    close();
    delete m_interfaceImpl;
}

bool Interface::open()
{
    if(m_interfaceImpl)
    {
        m_opened = m_interfaceImpl->open();
        return m_opened;
    }
    else
    {
        cout << "Error interface do not create" << endl;
    }

    return false;
}

bool Interface::close()
{
    cout << "Closing connection..." << endl;
    if(m_opened && m_interfaceImpl->close())
    {
        m_opened = false;
        return true;
    }
    return false;
}

int Interface::read(char *data, int size, int timeout)
{
    if(m_opened)
    {
        int res = m_interfaceImpl->read(data, size, timeout);
        return res;
    }
    else
    {
        cout << "Trying read in closed state" << endl;
        return 0;
    }
}

int Interface::read(char *data, int size, int *timeout)
{
    if(!timeout)
    {
        cout << "Calling Connection::read with NULL timeout variable" << endl;
        return 0;
    }
    timeval tms1, tms2;
    gettimeofday(&tms1, 0);
    int res = read(data, size, *timeout);
    gettimeofday(&tms2, 0);
    *timeout -= (tms2.tv_sec-tms1.tv_sec)*1000000 + (tms2.tv_usec-tms1.tv_usec);
    if(*timeout<0) *timeout=0;
    return res;
}

int Interface::write(const char *data, int size)
{
    if(m_opened)
    {
        int res = m_interfaceImpl->write(data, size);
        return res;
    }
    else
    {
        cout << "Trying write in closed state" << endl;
        return 0;
    }
}
