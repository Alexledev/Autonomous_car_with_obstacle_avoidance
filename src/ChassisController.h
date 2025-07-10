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

       const float baseSpeed = 130;

       const unsigned long interval = 1000; // ms
       unsigned long prevTime = 0;

       bool pauseUntilDone();
    public:
        ChassisController(MotorPins lPins, MotorPins rPins): leftPins(lPins), rightPins(rPins)
        {
            
        }

        ~ChassisController(){
            leftMotor = nullptr;
            rightMotor = nullptr;
        }

        void init()
        {
            leftMotor = new DCMotorController(leftPins);
            rightMotor = new DCMotorController(rightPins);
        }

        void forward(int speed);
        bool backward();
        void stop();

        bool turnLeft();
        bool turnRight();
        bool backSwivelRight();
        bool backSwivelLeft();

        void resumeTime();
};

#endif