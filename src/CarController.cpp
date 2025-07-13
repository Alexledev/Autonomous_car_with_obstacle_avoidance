#include "CarController.h"
#include "Utilities.h"
#include "Arduino.h"

bool CarController::detectObstacles()
{    
    int val = lr.getRangeInMM();
    return 150 < val && val < 450;      
}

void CarController::drive(int velocity)
{       
    
    velocity = chassis->readSpeedInput()/5;   

    if (inFrontOfObstacle == false && lr.collectData() && CarController::detectObstacles())
    {       
        chassis->stop();
        delay(100);
        inFrontOfObstacle = true;     
          
    }

    // avoidObstacles(turret->lowerRangeL, turret->upperRangeL, turret->lowerRangeR, turret->upperRangeR)
    if (inFrontOfObstacle == true && turret->lookAround(90) && avoidObstacles(turret->rangeL, turret->rangeR))
    {
        delay(500);
        inFrontOfObstacle = false;               
    }

    if (inFrontOfObstacle == false)
    {
        chassis->forward(velocity);

        DisplayVelocityAndDistance(velocity);
    }

    // display.displayLine(1, displayText);
}

void CarController::DisplayVelocityAndDistance(int velocity)
{
    int val = lr.getRangeInMM();

    String line[] = {"f:", String(velocity), "d:", String(val)};
    int length = sizeof(line) / sizeof(line[0]);

    String dispText = DisplayControl::appendTextWithSpace(line, length);
    Serial.println(dispText);

    display.displayLine(0, dispText, true);
}

// bool CarController::avoidObstacles(float lowerLeftArr[], float upperLeftArr[], float lowerRightArr[], float upperRightArr[])
// {
//     Serial.println("Lower Left:");
//     Utilities::printArr(lowerLeftArr, 20);
//     Serial.println("Upper Left:");
//     Utilities::printArr(upperLeftArr, 20);
//     Serial.println("Lower Right:");
//     Utilities::printArr(lowerRightArr, 20);
//     Serial.println("Upper Right:");
//     Utilities::printArr(upperRightArr, 20);

//     float lowerLeftValue = Utilities::mean(lowerLeftArr, 20);
//     float upperLeftValue = Utilities::mean(upperLeftArr, 20);
//     float lowerRightValue = Utilities::mean(lowerRightArr, 20);
//     float upperRightValue = Utilities::mean(upperRightArr, 20);

//     bool lowerLeftObs = hasObstacles(lowerLeftValue);
//     bool upperLeftObs = hasObstacles(upperLeftValue);
//     bool lowerRightObs = hasObstacles(lowerRightValue);
//     bool upperRightObs = hasObstacles(upperRightValue);

//     Serial.println("Lower Left:");
//     Serial.println(lowerLeftObs);
//     Serial.println("Upper Left:");
//     Serial.println(upperLeftObs);
//     Serial.println("Lower Right:");
//     Serial.println(lowerRightObs);
//     Serial.println("Upper Right:");
//     Serial.println(upperRightObs);

//     if (!lowerLeftObs && !upperLeftObs && !lowerRightObs && !upperRightObs)
//     {
//         // if ((lowerLeftValue > lowerRightValue || upperLeftValue > upperRightValue ) && swivelRight120()){
//         //     return true;     
//         // }

//         // if ((lowerLeftValue < lowerRightValue || upperLeftValue < upperRightValue) && swivelLeft120()){
//         //     return true;     
//         // }  

//         if ((lowerLeftValue + upperLeftValue > lowerRightValue + upperRightValue ) && swivelLeft120()){
//             return true;     
//         }
        
//         if ((lowerLeftValue + upperLeftValue < lowerRightValue + upperRightValue ) && swivelRight120()){
//             return true;     
//         }
//     }
//     else if (lowerLeftObs && upperLeftObs && lowerRightObs && upperRightObs)
//     {        
//         if ((lowerLeftValue + upperLeftValue > lowerRightValue + upperRightValue ) && swivelLeft120()){
//             return true;     
//         }
        
//         if ((lowerLeftValue + upperLeftValue < lowerRightValue + upperRightValue ) && swivelRight120()){
//             return true;     
//         }    
//     }
//     else if (upperRightObs && turningLeft120())
//     {
//         return true;
//     }
//     else if (upperLeftObs && turningRight120())
//     {
//         return true;
//     }
//     else if (lowerRightObs && turningLeft60())
//     {
//         return true;
//     }
//     else if (lowerLeftObs && turningRight60())
//     {
//         return true;
//     }

//     return false;
// }

bool CarController::avoidObstacles(float leftData[], float rightData[])
{
    Serial.println("Avoiding obstacles");

    float leftValue = Utilities::mean(leftData, 30);
    float rightValue = Utilities::mean(rightData, 30);

    bool leftObs = hasObstacles(leftValue);
    bool rightObs = hasObstacles(rightValue);

    DisplayObsDistances(leftValue, rightValue);

    if (!leftObs && !rightObs) // clear on both sides
    {
        if (leftValue > rightValue && swivelRight120()){
            return true;     
        }

        if (leftValue < rightValue && swivelLeft120()){
            return true;     
        }       
    }
    if (leftObs && rightObs) // obs on both sides
    {
        if (leftValue > rightValue && swivelRight120()){
            return true;     
        }

        if (leftValue < rightValue && swivelLeft120()){
            return true;     
        } 
    }
    if (leftObs && turningRight120())
    {
        return true;
    }
    if (rightObs && turningLeft120())
    {
       return true;
    }

    return false;
}

void CarController::DisplayObsDistances(float leftValue, float rightValue)
{
    String dispTextL = DisplayControl::appendTextWithSpace("L:", String(leftValue));
    String dispTextR = DisplayControl::appendTextWithSpace("R:", String(rightValue));

    displayText = DisplayControl::appendTextWithSpace(dispTextL, dispTextR);
}

bool CarController::turningLeft120()
{
    runningBackwards();
    while (chassis->turnLeftLong() == false);
    chassis->resumeTime();

    return true;
}

bool CarController::turningLeft60()
{
    runningBackwards();
    while (chassis->turnLeftShort() == false);
    chassis->resumeTime();

    return true;
}

bool CarController::turningRight120()
{
    runningBackwards();
    while (chassis->turnRightLong() == false); // hold until fully turned
    chassis->resumeTime();

    return true;
}

bool CarController::turningRight60()
{
    runningBackwards();
    while (chassis->turnRightShort() == false); // hold until fully turned
    chassis->resumeTime();

    return true;
}

bool CarController::runningBackwards()
{
    while (chassis->backward() == false);
    chassis->resumeTime();

    return true;
}

bool CarController::swivelLeft120()
{
    while (chassis->backSwivelLeft120() == false)
        ;
    chassis->resumeTime();

    return true;
}

bool CarController::swivelRight120()
{
    while (chassis->backSwivelRight120() == false)
        ;
    chassis->resumeTime();

    return true;
}

bool CarController::hasObstacles(int val)
{
    return val < detectionRange;
}


