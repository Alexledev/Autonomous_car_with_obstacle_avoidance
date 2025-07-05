#include "ChassisController.h"

// Move both motors forward at the given speed
void ChassisController::forward(int speed) {
    if (leftMotor) leftMotor->forward(speed);
    if (rightMotor) rightMotor->forward(speed);
}

// Move both motors backward at the given speed
void ChassisController::backward(int speed) {
    if (leftMotor) leftMotor->backward(speed);
    if (rightMotor) rightMotor->backward(speed);
}

// Stop both motors
void ChassisController::stop() {
    if (leftMotor) leftMotor->stop();
    if (rightMotor) rightMotor->stop();
}

// Turn left in place (axial turn)
void ChassisController::turnLeftAxial(int speed) {
    if (leftMotor) leftMotor->backward(speed);
    if (rightMotor) rightMotor->forward(speed);
}

// Turn right in place (axial turn)
void ChassisController::turnRightAxial(int speed) {
    if (leftMotor) leftMotor->forward(speed);
    if (rightMotor) rightMotor->backward(speed);
}

// Turn left with a radial turn (left motor slower, right motor faster)
void ChassisController::turnLeftRadial(int speed) {
    if (leftMotor) leftMotor->stop();
    if (rightMotor) rightMotor->forward(speed);
}

// Turn right with a radial turn (right motor slower, left motor faster)
void ChassisController::turnRightRadial(int speed) {
    if (leftMotor) leftMotor->forward(speed);
    if (rightMotor) rightMotor->stop();
}