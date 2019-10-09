# PairingCheck
Uniform, cross-platform program cheking connection RS-232, Eth. Type of communication set by configs files. The client sends the selected file to the server.
Working with the RS232 interface is implemented using wrapper classes that implement the "posix termios" interface for both Linux and Windows. So a class WinSerial is a termios porting for Windows C++.

# For build in Windows
qmake PairingCheck_win.pro 
make

# For build in Linux
qmake PairingCheck_lnx.pro 
make

# Run program
In run_scripts expamples for run program scripts.
