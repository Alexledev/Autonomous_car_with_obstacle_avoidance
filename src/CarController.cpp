#include "CarController.h"
#include "Arduino.h"

void CarController::drive(int velocity)
{
    if (inFrontOfObstacle == false && CarController::detectObstacles())
    {
        chassis->stop();
        delay(500);
        inFrontOfObstacle = true;
        display.displayLine(0, "has obs", true);
    }

    if (inFrontOfObstacle == true && turret->lookAround(90) && avoidObstacles(turret->dir[0], turret->dir[1]))
    {
        delay(1000);
        inFrontOfObstacle = false;
    }

    if (inFrontOfObstacle == false)
    {
        chassis->forward(velocity);
        display.displayLine(0, "forwards", true);
    }

    display.displayLine(1, displayText);
}

bool CarController::avoidObstacles(unsigned int leftValue, unsigned int rightValue)
{
    Serial.print("Left: ");
    Serial.print(leftValue);

    Serial.print(" Right: ");
    Serial.println(rightValue);

    bool leftObs = hasObstacles(leftValue);
    bool rightObs = hasObstacles(rightValue);

    String dispTextL = DisplayControl::appendTextWithSpace("L:", String(leftValue));
    String dispTextR = DisplayControl::appendTextWithSpace("R:", String(rightValue));

    displayText = DisplayControl::appendTextWithSpace(dispTextL, dispTextR);

    if (!leftObs && !rightObs) // clear on both sides
    {
        if (leftValue > rightValue && swivelRight()){
            return true;     
        }

        if (leftValue < rightValue && swivelLeft()){
            return true;     
        }       
    }
    if (leftObs && rightObs) // obs on both sides
    {
        if (leftValue > rightValue && swivelRight()){
            return true;     
        }

        if (leftValue < rightValue && swivelLeft()){
            return true;     
        } 
    }
    if (leftObs && turningRight())
    {
        return true;
    }
    if (rightObs && turningLeft())
    {
       return true;
    }

    return false;
}

bool CarController::turningLeft()
{
    runningBackwards();
    while (chassis->turnLeft60Deg() == false);
    chassis->resumeTime();

    return true;
}

bool CarController::turningRight()
{
    runningBackwards();
    while (chassis->turnRight60Deg() == false); // hold until fully turned
    chassis->resumeTime();

    return true;
}

bool CarController::runningBackwards()
{
    while (chassis->backward() == false);
    chassis->resumeTime();

    return true;
}

bool CarController::swivelLeft()
{
    while (chassis->backSwivelLeft() == false)
        ;
    chassis->resumeTime();

    return true;
}

bool CarController::swivelRight()
{
    while (chassis->backSwivelRight() == false)
        ;
    chassis->resumeTime();

    return true;
}

bool CarController::hasObstacles(int val)
{
    return val < detectionRange;
}

bool CarController::detectObstacles()
{
    int vd = turret->getRawData();
    return hasObstacles(vd);
}
