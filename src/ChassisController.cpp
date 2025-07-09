#include "ChassisController.h"
#include "Arduino.h"

// Move both motors forward at the given speed
void ChassisController::forward(int speed) {

    if (leftMotor) leftMotor->forward(speed);    
    if (rightMotor) rightMotor->forward(speed);
    
}


// Stop both motors
void ChassisController::stop() {
    if (leftMotor) leftMotor->stop();
    if (rightMotor) rightMotor->stop();
}

// Turn left in place (axial turn)
bool ChassisController::turnLeftAxial(int speed) {

    if (leftMotor) leftMotor->backward(speed);
    if (rightMotor) rightMotor->forward(speed);

    return true;
}

// Turn right in place (axial turn)
bool ChassisController::turnRightAxial(int speed) {

    if (leftMotor) leftMotor->forward(speed);
    if (rightMotor) rightMotor->backward(speed);

    return true;
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

bool ChassisController::pauseUntilDone()
{
    unsigned long currentTime = millis();
    
    if (prevTime == 0){
        prevTime = currentTime;
    }

    return currentTime - prevTime >= interval;  // 1 second

}

bool ChassisController::turnLeft60Deg() {
    
    if (pauseUntilDone()) // >= 1 second
    {       
        stop();
        return true;
    }
   
    if (leftMotor)
         leftMotor->backward(baseSpeed);
    if (rightMotor) 
        rightMotor->forward(baseSpeed*1.2);

   return false;
}

bool ChassisController::turnRight60Deg() {

    if (pauseUntilDone()) // >= 1 second
    {       
        stop();
        return true;
    }

    if (leftMotor)
         leftMotor->forward(baseSpeed*1.2);
    if (rightMotor) 
        rightMotor->backward(baseSpeed);

   return false;
}

bool ChassisController::backSwivelRight() {
    
    if (pauseUntilDone()) // >= 1 second
    {       
        stop();
        return true;
    }
   
    if (leftMotor)
        leftMotor->backward(250);
    if (rightMotor) 
        rightMotor->stop();

   return false;
}

bool ChassisController::backSwivelLeft() {
    
    if (pauseUntilDone()) // >= 1 second
    {       
        stop();
        return true;
    }
   
    if (leftMotor)
        leftMotor->stop();
    if (rightMotor) 
        rightMotor->backward(250);

   return false;
}

// Move both motors backward at the given speed
bool ChassisController::backward() {

    if (pauseUntilDone()) // >= 1 second
    {       
        stop();
        return true;
    }

    if (leftMotor)
         leftMotor->backward(baseSpeed);
    if (rightMotor) 
        rightMotor->backward(baseSpeed);

   return false;
}

void ChassisController::resumeTime()
{
    prevTime = 0;
}