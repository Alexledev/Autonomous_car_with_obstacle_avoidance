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

bool ChassisController::pauseUntilDone()
{
    unsigned long currentTime = millis();
    
    if (prevTime == 0){
        prevTime = currentTime;
    }

    return currentTime - prevTime >= interval;  // 1 second

}

bool ChassisController::turnLeftLong() { // around 120 deg
    
    return turnAxial(baseSpeed*1.2, baseSpeed*1.2, false);
}

bool ChassisController::turnLeftShort() { 
    
    return turnAxial(baseSpeed*0.9, baseSpeed*0.9, false);
}

bool ChassisController::turnRightLong() {

    return turnAxial(baseSpeed*1.2, baseSpeed*1.2, true);
}

bool ChassisController::turnRightShort() {

    return turnAxial(baseSpeed*0.9, baseSpeed*0.9, true);
}

bool ChassisController::turnAxial(int LeftSpd, int RightSpd, bool turnRight){
    if (pauseUntilDone()) // >= 1 second
    {       
        stop();
        return true;
    }

    if (turnRight)
    {
        leftMotor->forward(LeftSpd);
        rightMotor->backward(RightSpd);
    }
    else
    {        
        leftMotor->backward(LeftSpd);
        rightMotor->forward(RightSpd);
    }
    

   return false;
}

bool ChassisController::backSwivelRight60() {
    
    return backSwivel(125, true);
}

bool ChassisController::backSwivelRight120() {
    
    return backSwivel(250, true);
}

bool ChassisController::backSwivelLeft60() {
    
     return backSwivel(125, false);
}

bool ChassisController::backSwivelLeft120() {
    
    return backSwivel(250, false);
}

bool ChassisController::backSwivel(int value, bool turnRight) {
    
    if (pauseUntilDone()) // >= 1 second
    {       
        stop();
        return true;
    }

    if (turnRight)
    {       
        leftMotor->backward(value);
        rightMotor->stop();
    }
    else
    {       
        leftMotor->stop();      
        rightMotor->backward(value);
    }     

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

int ChassisController::readSpeedInput()
{
    return analogRead(speedSetPin);
}