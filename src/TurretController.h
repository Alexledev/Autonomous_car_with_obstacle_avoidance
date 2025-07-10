#include <Servo.h>
#include <UltrasonicController.h>
#include <Arduino.h>

#ifndef TURRET_CONTROLLER_H
#define TURRET_CONTROLLER_H

enum Directions {
    MIDDLE,
    RIGHT,
    LEFT,
    STOP
};

struct TurretValue
{
    Directions direction;
    int value[180];
};


class TurretController
{
private:
    Servo swivelMotor;
    UltrasonicController ultraSensor;

    int step = 1;  
    unsigned long lastMoveTime=0;
    int sPin;
    int pos = 0; 
    
    unsigned int sumSensorValues = 0;
    int sampleCount = 0;
    int recentSensorValue = 0;

    unsigned long lastTime = 0;

public:
    TurretController(int servoPin): sPin(servoPin), ultraSensor(A0){
        
    }

    void init();
    bool lookAround(int starting);
    
    bool nextSampleData();
    int getCurrentData();  
    
    int getRawData();

    float rangeL[30];
    float rangeR[30];

};

#endif