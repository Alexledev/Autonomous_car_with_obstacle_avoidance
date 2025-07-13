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

       int speedSetPin = A2;

       const float baseSpeed = 130;

       const unsigned long interval = 1000; // ms
       unsigned long prevTime = 0;

       bool backSwivel(int value, bool turnRight);
       bool turnAxial(int LeftSpd, int RightSpd, bool turnRight);
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
            pinMode(speedSetPin, INPUT);
        }

        void forward(int speed);
        bool backward();
        void stop();

        bool turnLeftLong();
        bool turnRightLong();
        
        bool turnLeftShort();
        bool turnRightShort();


        bool backSwivelRight60();
        bool backSwivelLeft60();

        bool backSwivelRight120();
        bool backSwivelLeft120();

        void resumeTime();

        int readSpeedInput();
};

#endif