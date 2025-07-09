#include "TurretController.h"
#include <Arduino.h>

void TurretController::init(){
    swivelMotor.attach(sPin);
    // TurretController::lookForward();
}

void TurretController::lookForward() {
    // Set the servo to the forward position (e.g., 90 degrees)
    swivelMotor.write(FORWARDALIGN);
    pos = 90;
}

void TurretController::scan(int startDegrees, int endDegrees) {
    if (pos == 0){
        pos = startDegrees;    
    }
    
    
    unsigned long currentTime = millis();

    if (currentTime - lastMoveTime >= 30) {  // move every 30 ms
        swivelMotor.write(pos);
        currentSensorValue = ultraSensor.getValue();
        pos += step;

        if (pos >= endDegrees || pos <= startDegrees) {
            step = -step; // reverse direction
        }
        lastMoveTime = currentTime;
    }
}

void TurretController::collectData(){

    currentSensorValue = ultraSensor.getValue();    
    dir[pos-1] = currentSensorValue;

}

bool TurretController::lookAround(int start)
{
    
    if (pos == 0){
        pos = start;    
    }
     
    unsigned long currentTime = millis();

    if (currentTime - lastMoveTime >= 15) {  // move every 30 ms       
        swivelMotor.write(pos);              

        pos += step;

        if (pos >= 150 && pos < 180){ // left data
            while(!nextSampleData());
            dir[0] = getCurrentData();
        }
        else if (pos < 30 && pos > 0) // right data
        {
            while(!nextSampleData());    
            dir[1] = getCurrentData();      
        }

        if (pos >= 180) {
            step = -step; // reverse direction

            // while(!nextSampleData());
            // dir[0] = getCurrentData();
        }
        else if (pos <= 1){
            step = -step;           

            // while(!nextSampleData());    
            // dir[1] = getCurrentData();           
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