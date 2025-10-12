#ifndef RECEIVE_H
#define RECEIVE_H

#include "serial.h"
#include "gpio.h"

class DataReceiver {
public:
    DataReceiver(SerialPort &serial, int ledTemp, int ledLight, int irSensorPin,int motionLed);
    void processLoop();

private:
    SerialPort &serial;
    int ledTemp;
    int ledLight;
    int motionLed;
    int irSensorPin;
};

#endif // RECEIVE_H