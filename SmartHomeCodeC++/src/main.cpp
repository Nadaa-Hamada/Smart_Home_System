#include "gpio.h"
#include "serial.h"
#include "recieve.h"

int main() {
    int ledTemp = 17;
    int ledLight = 27;
    int irSensor = 22; // IR sensor GPIO pin

    setupGPIO(ledTemp, "out");
    setupGPIO(ledLight, "out");

    SerialPort serial("/dev/ttyACM0");
    if (!serial.openPort()) return 1;

    DataReceiver receiver(serial, ledTemp, ledLight, irSensor);
    receiver.processLoop();

    return 0;
}
