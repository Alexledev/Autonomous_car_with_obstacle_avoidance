#include "DCMotorController.h"
#include <Arduino.h>

// Move motor forward
void DCMotorController::forward(int speed) {
    digitalWrite(forwardPin, HIGH);
    digitalWrite(backwardPin, LOW);
    analogWrite(enPin, speed);
}

// Move motor backward
void DCMotorController::backward(int speed) {
    digitalWrite(forwardPin, LOW);
    digitalWrite(backwardPin, HIGH);
    analogWrite(enPin, speed);
}

void DCMotorController::stop(){
    digitalWrite(forwardPin, HIGH);
    digitalWrite(backwardPin, HIGH);
    analogWrite(enPin, 0);
}