#include <Arduino.h>

#ifndef US_CONTROLLER_H
#define US_CONTROLLER_H

class UltrasonicController
{
private:
    int pin;
public:
    UltrasonicController(int sensorPin): pin(sensorPin)
    {
        pinMode(pin, INPUT);
    }
    
    unsigned int getValue();
};

#endif