#include "gpio.h"
#include "serial.h"
#include "recieve.h"

int main() {
    const int ledTemp = 17;
    const int ledLight = 27;
    const int irSensor = 22; // IR sensor GPIO pin
    const int motionLed = 24;
    setupGPIO(ledTemp, "out");
    setupGPIO(ledLight, "out");
 setupGPIO(motionLed, "out");
  setupGPIO(irSensor, "in");


    SerialPort serial("/dev/ttyACM0");
    if (!serial.openPort()) return 1;

    DataReceiver receiver(serial, ledTemp, ledLight, irSensor, motionLed);
    receiver.processLoop();

    return 0;
}