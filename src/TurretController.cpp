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

    if (currentTime - lastMoveTime >= 30) {  // move every 15 ms       

        swivelMotor.write(pos);              

        pos += step;

        Serial.print("Sensor value: ");
        Serial.println(recentSensorValue);
        
        // old
        if (pos >= 150 && pos < 180){ // left data
            while(!nextSampleData());
            rangeL[(pos) - 150] = getCurrentData();
        }
        else if (pos <= 30 && pos > 0)  // right data
        {
            while(!nextSampleData());  
            rangeR[(pos) - 1] = getCurrentData();              
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


// bool TurretController::lookAroundNew(int start)
// {
//     if (pos == 0){
//         pos = start;    
//     }
     
//     unsigned long currentTime = millis();

//     if (currentTime - lastMoveTime >= 30) {  // move every 15 ms       

//         swivelMotor.write(pos);              

//         pos += step;

//         Serial.print("Sensor value: ");
//         Serial.println(recentSensorValue);

//         if (pos >= 160 && pos < 180)
//         { // left data
//             while(!nextSampleData());
//             lowerRangeL[(pos) - 160] = getCurrentData();
//         }
//         else if (pos >= 135 && pos <= 155)
//         {
//             while(!nextSampleData());
//             upperRangeL[(pos) - 135] = getCurrentData();
//         }
//         else if (pos <= 20 && pos > 0)  // right data
//         {
//             while(!nextSampleData());  
//             lowerRangeR[(pos) - 1] = getCurrentData();              
//         }
//         else if (pos <= 45 && pos >= 25)
//         {
//             while(!nextSampleData());  
//             upperRangeR[(pos) - 25] = getCurrentData();              
//         }

//         if (pos >= 180) {
//             step = -step; // reverse direction          
//         }
//         else if (pos <= 1){
//             step = -step;                   
//         }

//         lastMoveTime = currentTime;

//         if (step > 0 && pos == start){
//            return true;
//         }       
//     }
  
//     return false;
// }

bool TurretController::nextSampleData(){

    unsigned long currentTime = millis();

    if (currentTime - lastTime > 10)
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