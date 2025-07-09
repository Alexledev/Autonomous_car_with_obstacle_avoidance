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

       const float wheelCircumference = 6.6*3.14 / 100; // m
       const float distanceBetweenWheels = 13.5 / 100; // m    

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

        bool turnLeftAxial(int speed);
        bool turnRightAxial(int speed);
        void turnLeftRadial(int speed);
        void turnRightRadial(int speed);

        bool turnLeft60Deg();
        bool turnRight60Deg();
        bool backSwivelRight();
        bool backSwivelLeft();

        void resumeTime();

        // float calcCarRotationRad(float leftRotations, float rightRotations)
        // {
        //     float leftDistanceTravelled = leftRotations * wheelCircumference;
        //     float rightDistanceTravelled = rightRotations * wheelCircumference;

        //     float rot = (rightDistanceTravelled - leftDistanceTravelled)/distanceBetweenWheels;
        //     return rot; // + left rotation | - right rotation
        // }

        // float calcWheelRotation(float timePassed, float speed)
        // {
        //     float distance = speed * timePassed;
        //     float rot = distance / wheelCircumference;

        //     return rot;
        // }

};

#endif