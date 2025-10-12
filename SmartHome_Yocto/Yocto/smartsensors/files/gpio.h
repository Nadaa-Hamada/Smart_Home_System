#ifndef GPIO_H
#define GPIO_H

#include <string>

void setupGPIO(int pin, const std::string &direction);
void writeGPIO(int pin, int value);
int readGPIO(int pin);

#endif // GPIO_UTILS_H