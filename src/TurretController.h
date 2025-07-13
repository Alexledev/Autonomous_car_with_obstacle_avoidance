#include <Servo.h>
#include <UltrasonicController.h>

#ifndef TURRET_CONTROLLER_H
#define TURRET_CONTROLLER_H

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
    // bool lookAroundNew(int starting);
    
    bool nextSampleData();
    int getCurrentData();  
    
    int getRawData();

    float rangeL[30];
    float rangeR[30];

    // float lowerRangeL[20]; // 180-160
    // float upperRangeL[20]; // 155-135

    // float lowerRangeR[20]; // 0-20
    // float upperRangeR[20]; // 25-45
};

#endif