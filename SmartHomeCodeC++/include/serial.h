#ifndef SERIAL_H
#define SERIAL_H


#include <string>

class SerialPort {
public:
    SerialPort(const std::string &portName, int baudRate = 115200);
    ~SerialPort();

    bool openPort();
    void closePort();
    int readData(char *buffer, int size);

private:
    bool configurePort();

    std::string portName;
    int baudRate;
    int fd;
};
#endif // SERIAL_H
