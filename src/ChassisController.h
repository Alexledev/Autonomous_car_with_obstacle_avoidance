#include "DCMotorController.h"
#ifndef CHASSIS_CONTROLLER_H
#define CHASSIS_CONTROLLER_H


class ChassisController
{
    private:
       MotorPins leftPins;
       MotorPins rightPins;

       DCMotorController *leftMotor = nullptr;
       DCMotorController *rightMotor = nullptr;
    public:
        ChassisController(MotorPins lPins, MotorPins rPins): leftPins(lPins), rightPins(rPins)
        {
            leftMotor = new DCMotorController(lPins);
            rightMotor = new DCMotorController(rPins);
        }

        ~ChassisController(){
            leftMotor = nullptr;
            rightMotor = nullptr;
        }

        void forward(int speed);
        void backward(int speed);
        void stop();

        void turnLeftAxial(int speed);
        void turnRightAxial(int speed);
        void turnLeftRadial(int speed);
        void turnRightRadial(int speed);
};

#endif