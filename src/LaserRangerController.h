#include <Wire.h>
#include <VL53L0X.h>

#ifndef LR_CONTROLLER_H
#define LR_CONTROLLER_H

class LaserRangerController
{
private:
    VL53L0X sensor;

public:
    void init()
    {
        Wire.begin();
        sensor.init();
        sensor.startContinuous();        
    }
   
    const int arrLen = 8;
    int sensorData = 0;
    float arr[8];

    bool collectData();
    float median3(float a, float b, float c);
    unsigned long getRangeInMM();
};

#endif