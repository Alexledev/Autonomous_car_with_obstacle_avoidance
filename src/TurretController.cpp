#include "TurretController.h"
#include <Arduino.h>

void TurretController::init(){
    swivelMotor.attach(sPin);
    swivelMotor.write(90);
}

bool TurretController::lookAround(int start)
{
    if (pos == 0){
        pos = start;    
    }
     
    unsigned long currentTime = millis();

    if (currentTime - lastMoveTime >= 15) {  // move every 15 ms       
        swivelMotor.write(pos);              

        pos += step;

        if (pos >= 150 && pos < 180){ // left data
            while(!nextSampleData());
            rangeL[pos-150] = getCurrentData();
        }
        else if (pos <= 30 && pos > 0) // right data
        {
            while(!nextSampleData());  
            rangeR[pos-1] = getCurrentData();              
        }

        if (pos >= 180) {
            step = -step; // reverse direction          
        }
        else if (pos <= 1){
            step = -step;                   
        }

        lastMoveTime = currentTime;

        if (step > 0 && pos == start){
           return true;
        }       
    }
  
    return false;
}

bool TurretController::nextSampleData(){

    unsigned long currentTime = millis();

    if (currentTime - lastTime > 8)
    {  
        sumSensorValues += ultraSensor.getValue();
        sampleCount++;
        lastTime = currentTime;
    }
    
    if (sampleCount >= 5) // sample size = 10
    {
        recentSensorValue = sumSensorValues/5;
       
        sampleCount = 0;
        sumSensorValues = 0;
        return true;
    }

    return false;
}

int TurretController::getCurrentData()
{
    return recentSensorValue;
}

int TurretController::getRawData()
{
    return ultraSensor.getValue();
}