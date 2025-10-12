#include "serial.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>

using namespace std;

SerialPort::SerialPort(const string &portName, int baudRate)
    : portName(portName), baudRate(baudRate), fd(-1) {}

SerialPort::~SerialPort() { closePort(); }

bool SerialPort::openPort() {
    fd = open(portName.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        cerr << "Error opening serial port " << portName << endl;
        return false;
    }
    return configurePort();
}

void SerialPort::closePort() {
    if (fd >= 0) {
        close(fd);
        fd = -1;
    }
}

int SerialPort::readData(char *buffer, int size) {
    if (fd < 0) return -1;
    return read(fd, buffer, size);
}

bool SerialPort::configurePort() {
    if (fd < 0) return false;

    struct termios tty;
    memset(&tty, 0, sizeof tty);
    if (tcgetattr(fd, &tty) != 0) {
        cerr << "Error from tcgetattr\n";
        return false;
    }

    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN]  = 1;
    tty.c_cc[VTIME] = 1;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    return (tcsetattr(fd, TCSANOW, &tty) == 0);
}
