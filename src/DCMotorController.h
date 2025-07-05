#include <Arduino.h>
#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

struct MotorPins
{
    int forwardPin;
    int backwardPin;
    int enPin;
};

class DCMotorController
{
    private:
        int forwardPin;
        int backwardPin;
        int enPin;

    public:
        DCMotorController(MotorPins motorPins): DCMotorController(motorPins.forwardPin, motorPins.backwardPin, motorPins.enPin)
        {                   
        }

        DCMotorController(int fPin, int bPin, int ePin): forwardPin(fPin), backwardPin(bPin), enPin(ePin)
        {
            pinMode(fPin, OUTPUT);
            pinMode(bPin, OUTPUT);  
            pinMode(ePin, OUTPUT);          
        }

        void forward(int speed);
        void backward(int speed);
        void stop();
};

#endif