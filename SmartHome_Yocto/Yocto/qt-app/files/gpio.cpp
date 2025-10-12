#include "gpio.h"
#include <fstream>
#include <iostream>
#include <unistd.h>

using namespace std;


void setupGPIO(int pin, const std::string& direction) {
    std::ofstream exportFile("/sys/class/gpio/export");
    exportFile << pin;
    exportFile.close();

    std::ofstream directionFile("/sys/class/gpio/gpio" + std::to_string(pin) + "/direction");
    directionFile << direction;
    directionFile.close();
}

void writeGPIO(int pin, int value) {
    std::ofstream valueFile("/sys/class/gpio/gpio" + std::to_string(pin) + "/value");
    valueFile << value;
    valueFile.close();
}
int readGPIO(int pin) {
    string path = "/run/gpio_" + to_string(pin) + ".txt";
    ifstream val(path);
    int value = 0;
    if (val.is_open()) {
        val >> value;
        val.close();
    } else {
        cerr << "Failed to open " << path << endl;
    }
    return value;
}
