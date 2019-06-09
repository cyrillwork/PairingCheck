#include "winserial.h"

using namespace win_serial;

WinSerial::WinSerial():
    m_Handle(static_cast<HANDLE>(INVALID_HANDLE_VALUE))
{
}

WinSerial::~WinSerial()
{
    close(fd);
}

bool WinSerial::IsOK() const
{
    return m_Handle != INVALID_HANDLE_VALUE;
}

int WinSerial::open(const char *pathname, int flags)
{
    int baudrate = 9600;
    ++fd;

    std::string port(pathname);
    std::wstring str1(port.begin(), port.end());

    m_Handle =
            CreateFile(
                str1.c_str(),
                GENERIC_READ | GENERIC_WRITE,
                0,
                nullptr,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                nullptr);

    if(m_Handle == INVALID_HANDLE_VALUE)
    {
        return -1;
    }

    SetCommMask(m_Handle, EV_RXCHAR);
    SetupComm(m_Handle, 1500, 1500);

    COMMTIMEOUTS CommTimeOuts;
    CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
    CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
    CommTimeOuts.ReadTotalTimeoutConstant = TIMEOUT;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
    CommTimeOuts.WriteTotalTimeoutConstant = TIMEOUT;

    if(!SetCommTimeouts(m_Handle, &CommTimeOuts))
    {
        CloseHandle(m_Handle);
        m_Handle = static_cast<HANDLE>(INVALID_HANDLE_VALUE);
        return -1;
    }

    DCB ComDCM;

    memset(&ComDCM,0,sizeof(ComDCM));
    ComDCM.DCBlength = sizeof(DCB);
    GetCommState(m_Handle, &ComDCM);
    ComDCM.BaudRate = DWORD(baudrate);
    ComDCM.ByteSize = 8;
    ComDCM.Parity = NOPARITY;
    ComDCM.StopBits = ONESTOPBIT;
    ComDCM.fAbortOnError = TRUE;
    ComDCM.fDtrControl = DTR_CONTROL_DISABLE;
    ComDCM.fRtsControl = RTS_CONTROL_DISABLE;
    ComDCM.fBinary = TRUE;
    ComDCM.fParity = FALSE;
    ComDCM.fInX = FALSE;
    ComDCM.fOutX = FALSE;
    ComDCM.XonChar = 0;
    ComDCM.XoffChar = static_cast<char>(0xFF);
    ComDCM.fErrorChar = FALSE;
    ComDCM.fNull = FALSE;
    ComDCM.fOutxCtsFlow = FALSE;
    ComDCM.fOutxDsrFlow = FALSE;
    ComDCM.XonLim = 128;
    ComDCM.XoffLim = 128;

    if(!SetCommState(m_Handle, &ComDCM))
    {
        CloseHandle(m_Handle);
        m_Handle = INVALID_HANDLE_VALUE;
        return -1;
    }

    return fd;
}

int WinSerial::close(int fd)
{
    if(m_Handle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_Handle);
        m_Handle = INVALID_HANDLE_VALUE;
    }
}

int WinSerial::select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout)
{
    SetCommMask(m_Handle, EV_RXCHAR);
    DWORD dwEventMask;
    WaitCommEvent(m_Handle, &dwEventMask, nullptr);

    if (dwEventMask == EV_RXCHAR)
        return fd;
    else
        return -1;
}


size_t WinSerial::write(const char* buff, size_t len)
{
    DWORD feedback = 0;

    if(m_Handle == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    WriteFile(m_Handle, buff, static_cast<DWORD>(len), &feedback, nullptr);

    // In some cases it's worth uncommenting
    //FlushFileBuffers(m_Handle);

    return feedback;
}

size_t WinSerial::read(char *buff, size_t len)
{
    if(m_Handle == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    //DWORD begin = GetTickCount();
    DWORD feedback = 0;

    if(!ReadFile(m_Handle, buff, len, &feedback, nullptr))
    {
        return 0;
    }

    return feedback;

//    unsigned char* buf = &data[0];
//    DWORD len = (DWORD)data.size();

//    int attempts = 3;
//    while(len && (attempts || (GetTickCount()-begin) < (DWORD)TIMEOUT/3)) {

//        if(attempts) attempts--;

//        if(!ReadFile(m_Handle, buf, len, &feedback, NULL)) {
//            CloseHandle(m_Handle);
//            m_Handle = INVALID_HANDLE_VALUE;
//            throw TTYException();
//        }

//        assert(feedback <= len);
//        len -= feedback;
//        buf += feedback;

//    }

}

/*nbyte 0->7*/
int getByte(tcflag_t flag, int nbyte, int nibble)
{

    int byte;
    if (nibble == 1)
        byte = (flag >> (8 * (nbyte)) & 0x0f);
    else
        byte = (flag >> (8 * (nbyte)) & 0xf0);
    return byte;
}
//INPUT FUNCTIONS

int getIXOptions(tcflag_t flag)
{
#define i_IXOFF 0x01
#define i_IXON 0x02
#define i_IXOFF_IXON 0x03
#define i_PARMRK 0x04
#define i_PARMRK_IXOFF 0x05
#define i_PARMRK_IXON 0x06
#define i_PARMRK_IXON_IXOFF 0x07

    int byte = getByte(flag, 1, 1);

    return byte;
}

//LOCALOPT FUNCTIONS

int getEchoOptions(tcflag_t flag)
{

#define l_NOECHO 0x00
#define l_ECHO 0x01
#define l_ECHO_ECHOE 0x03
#define l_ECHO_ECHOK 0x05
#define l_ECHO_ECHONL 0x09
#define l_ECHO_ECHOE_ECHOK 0x07
#define l_ECHO_ECHOE_ECHONL 0x0b
#define l_ECHO_ECHOE_ECHOK_ECHONL 0x0f
#define l_ECHO_ECHOK_ECHONL 0x0d
#define l_ECHOE 0x02
#define l_ECHOE_ECHOK 0x06
#define l_ECHOE_ECHONL 0x0a
#define l_ECHOE_ECHOK_ECHONL 0x0e
#define l_ECHOK 0x04
#define l_ECHOK_ECHONL 0x0c
#define l_ECHONL 0x08

    int byte = getByte(flag, 1, 1);
    return byte;
}

int getLocalOptions(tcflag_t flag) {

#define l_ICANON 0x10
#define l_ICANON_ISIG 0x50
#define l_ICANON_IEXTEN 0x30
#define l_ICANON_NOFLSH 0x90
#define l_ICANON_ISIG_IEXTEN 0x70
#define l_ICANON_ISIG_NOFLSH 0xd0
#define l_ICANON_IEXTEN_NOFLSH 0xb0
#define l_ICANON_ISIG_IEXTEN_NOFLSH 0xf0
#define l_ISIG 0x40
#define l_ISIG_IEXTEN 0x60
#define l_ISIG_NOFLSH 0xc0
#define l_ISIG_IEXTEN_NOFLSH 0xe0
#define l_IEXTEN 0x20
#define l_IEXTEN_NOFLSH 0xa0
#define l_NOFLSH 0x80

    int byte = getByte(flag, 1, 0);
    return byte;
}

int getToStop(tcflag_t flag) {

#define l_TOSTOP 0x01

    int byte = getByte(flag, 1, 1);
    return byte;
}

//CONTROLOPT FUNCTIONS

int getCharSet(tcflag_t flag)
{

    //FLAG IS MADE UP OF 8 BYTES, A FLAG IS MADE UP OF A NIBBLE -> 4 BITS, WE NEED TO EXTRACT THE SECOND NIBBLE (1st) FROM THE FIFTH BYTE (6th).
    int byte = getByte(flag, 1, 1);

    switch (byte) {

    case 0X0:
        return CS5;
        break;

    case 0X4:
        return CS6;
        break;

    case 0X8:
        return CS7;
        break;

    case 0Xc:
        return CS8;
        break;

    default:
        return CS8;
        break;
    }
}

int getControlOptions(tcflag_t flag)
{

#define c_ALL_ENABLED 0xd0
#define c_PAREVEN_CSTOPB 0x50
#define c_PAREVEN_NOCSTOPB 0x40
#define c_PARODD_NOCSTOPB 0xc0
#define c_NOPARENB_CSTOPB 0x10
#define c_ALL_DISABLED 0x00

    int byte = getByte(flag, 1, 0);
    return byte;
}



int WinSerial::tcsetattr(int optional_actions, const termios* termios_p)
{
    int ret = 0;

    //Store flags into local variables
    tcflag_t iflag = termios_p->c_iflag;
    tcflag_t lflag = termios_p->c_lflag;
    tcflag_t cflag = termios_p->c_cflag;
    tcflag_t oflag = termios_p->c_oflag;

    /*****************************************
    iflag
    *****************************************/

    int IX = getIXOptions(iflag);

    if ((IX == i_IXOFF_IXON) || (IX == i_PARMRK_IXON_IXOFF)) {

        SerialParams.fOutX = TRUE;
        SerialParams.fInX = TRUE;
        SerialParams.fTXContinueOnXoff = TRUE;
    }

    /*****************************************
    lflag
    *****************************************/

    int EchoOpt = getEchoOptions(lflag);
    int l_opt = getLocalOptions(lflag);
    int tostop = getToStop(lflag);

    //Missing parameters...

    /*****************************************
    cflag
    *****************************************/

    int CharSet = getCharSet(cflag);
    int c_opt = getControlOptions(cflag);

    switch (CharSet) {

    case CS5:
        SerialParams.ByteSize = 5;
        break;

    case CS6:
        SerialParams.ByteSize = 6;
        break;

    case CS7:
        SerialParams.ByteSize = 7;
        break;

    case CS8:
        SerialParams.ByteSize = 8;
        break;
    }

    switch (c_opt)
    {
    case c_ALL_ENABLED:
        SerialParams.Parity = ODDPARITY;
        SerialParams.StopBits = TWOSTOPBITS;
        break;
    case c_ALL_DISABLED:
        SerialParams.Parity = NOPARITY;
        SerialParams.StopBits = ONESTOPBIT;
        break;
    case c_PAREVEN_CSTOPB:
        SerialParams.Parity = EVENPARITY;
        SerialParams.StopBits = TWOSTOPBITS;
        break;
    case c_PAREVEN_NOCSTOPB:
        SerialParams.Parity = EVENPARITY;
        SerialParams.StopBits = ONESTOPBIT;
        break;
    case c_PARODD_NOCSTOPB:
        SerialParams.Parity = ODDPARITY;
        SerialParams.StopBits = ONESTOPBIT;
        break;
    case c_NOPARENB_CSTOPB:
        SerialParams.Parity = NOPARITY;
        SerialParams.StopBits = TWOSTOPBITS;
        break;
    }

    /*****************************************
    oflag
    *****************************************/

    /*int OP;
    if(oflag == OPOST)
    else ...*/
    //Missing parameters...

    /*****************************************
    special characters
    *****************************************/

    COMMTIMEOUTS timeouts = {};

    if (termios_p->c_cc[VEOF] != 0) SerialParams.EofChar = (char)termios_p->c_cc[VEOF];
    if (termios_p->c_cc[VINTR] != 0) SerialParams.EvtChar = (char)termios_p->c_cc[VINTR];

    if (termios_p->c_cc[VMIN] == 1)
    { //Blocking
        timeouts.ReadIntervalTimeout = 0;         // in milliseconds
        timeouts.ReadTotalTimeoutConstant = 0;    // in milliseconds
        timeouts.ReadTotalTimeoutMultiplier = 0;  // in milliseconds
        timeouts.WriteTotalTimeoutConstant = 0;   // in milliseconds
        timeouts.WriteTotalTimeoutMultiplier = 0; // in milliseconds
    }
    else
    { //Non blocking

        timeouts.ReadIntervalTimeout = termios_p->c_cc[VTIME] * 100;         // in milliseconds
        timeouts.ReadTotalTimeoutConstant = termios_p->c_cc[VTIME] * 100;    // in milliseconds
        timeouts.ReadTotalTimeoutMultiplier = termios_p->c_cc[VTIME] * 100;  // in milliseconds
        timeouts.WriteTotalTimeoutConstant = termios_p->c_cc[VTIME] * 100;   // in milliseconds
        timeouts.WriteTotalTimeoutMultiplier = termios_p->c_cc[VTIME] * 100; // in milliseconds
    }

    SetCommTimeouts(m_Handle, &timeouts);

    /*****************************************
    EOF
    *****************************************/
    ret = SetCommState(m_Handle, &SerialParams);

    if (ret != 0)
        return 0;
    else
        return -1;
}
