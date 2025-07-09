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
    const int FORWARDALIGN = 90;    
    unsigned int currentSensorValue = 0;
    
    unsigned int sumSensorValues = 0;
    int sampleCount = 0;
    int recentSensorValue = 0;

    unsigned long lastTime = 0;

    void turnLeft(int endDegrees);
    void collectData();

public:
    TurretController(int servoPin): sPin(servoPin), ultraSensor(A0){
        
    }

    void init();
    void lookForward();
    void scan(int startDegrees, int endDegrees);
    Directions scan(int range);
    bool lookAround(int starting);
    
    bool nextSampleData();
    int getCurrentData();  
    
    int getRawData();

    unsigned int dir[2];

};

#endif