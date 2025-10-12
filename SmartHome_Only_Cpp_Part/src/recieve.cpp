#include "recieve.h"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

DataReceiver::DataReceiver(SerialPort &serial, int ledTemp, int ledLight, int irSensorPin,int motinled)
    : serial(serial), ledTemp(ledTemp), ledLight(ledLight), irSensorPin(irSensorPin), motionLed(motionLed)
{
    setupGPIO(irSensorPin, "in");
}

void DataReceiver::processLoop()
{
    char buffer[100];
    int lightState = 0;

    while (true)
    {

        int n = serial.readData(buffer, sizeof(buffer) - 1);
        if (n > 0)
        {
            buffer[n] = '\0';
            string data(buffer);

            size_t tpos = data.find("TEMP:");
            size_t lpos = data.find("LIGHT:");
            if (tpos != string::npos && lpos != string::npos)
            {
                string tempStr = data.substr(tpos + 5, lpos - (tpos + 5));
                string lightStr = data.substr(lpos + 6);

                try
                {
                    int temp = stoi(tempStr);
                    int light = stoi(lightStr);

                    cout << "Temp=" << temp << " Light=" << light << endl;

                    writeGPIO(ledTemp, (temp > 30) ? 1 : 0);

                    if (readGPIO(irSensorPin) == 0 )
                    {
                        writeGPIO(motionLed, 1);

                        if(light < 300)
                        writeGPIO(ledLight, 1);
                        else
                        writeGPIO(ledLight, 0);

                    }
                    else 
                    {

                       writeGPIO(motionLed, 0);
                        writeGPIO(ledLight, 0);
                    }
                }
                catch (const invalid_argument &e)
                {
                    cerr << "Invalid data: " << data << endl;
                }
            }
        }
        usleep(500000);
    }
}
