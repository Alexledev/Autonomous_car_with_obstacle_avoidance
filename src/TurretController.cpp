#include "TurretController.h"
#include <Arduino.h>

void TurretController::init(){
    swivelMotor.attach(sPin);
    swivelMotor.write(0);
}

void TurretController::lookForward() {
    // Set the servo to the forward position (e.g., 90 degrees)
    swivelMotor.write(FORWARDALIGN);
}

void TurretController::scan(int startDegrees, int endDegrees) {
    if (pos == 0){
        pos = startDegrees;    
    }
    
    static int step = 2;   
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

void TurretController::scan(int range) {
    int w = range/2;
    int lower = FORWARDALIGN-w;
    int higher = FORWARDALIGN+w;

    TurretController::scan(lower, higher);
}

TurretValue TurretController::getViewData(int range)
{
    TurretController::scan(range);
    int w2 = range/3;
    int i1 = w2;
    int i2 = i1 + w2;
    
    TurretValue vals;
    vals.value = currentSensorValue;

    if (pos < i1){
        // Serial.print("right at: ");
        vals.direction = RIGHT;
    }
    else if (pos > i1 && pos < i2){
        // Serial.print("middle at: ");
        vals.direction = MIDDLE;
    }
    else if (pos > i2){
        // Serial.print("left at: ");
        vals.direction = LEFT;
    }
    // Serial.println(pos);

    return vals;
}