#include<gpio.h>
#include <fstream>
#include <unistd.h>
#include <iostream>

using namespace std;

void setupGPIO(int pin, const string &direction) {
    ofstream export_gpio("/sys/class/gpio/export");
    if (export_gpio.is_open()) {
        export_gpio << pin;
        export_gpio.close();
        usleep(100000);
    }

    ofstream dir("/sys/class/gpio/gpio" + to_string(pin) + "/direction");
    if (dir.is_open()) {
        dir << direction;
        dir.close();
    }
}

void writeGPIO(int pin, int value) {
    ofstream val("/sys/class/gpio/gpio" + to_string(pin) + "/value");
    if (val.is_open()) {
        val << value;
        val.close();
    }
}

int readGPIO(int pin) {
    ifstream val("/sys/class/gpio/gpio" + to_string(pin) + "/value");
    int value = 0;
    if (val.is_open()) {
        val >> value;
        val.close();
    }
    return value;
}
