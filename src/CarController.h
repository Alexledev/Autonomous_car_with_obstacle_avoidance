#include "TurretController.h"
#include "ChassisController.h"
// #include "UltrasonicController.h"
#include "DisplayControl.h"
#include "LaserRangerController.h"
#include <Arduino.h>

class CarController
{
private:
    TurretController *turret = nullptr;
    ChassisController *chassis = nullptr;    
    DisplayControl display;    
    LaserRangerController lr;

    bool inFrontOfObstacle = false;

    bool detectObstacles();
    int detectionRange = 450;
   
    unsigned long lastTime = 0;
  
    bool hasObstacles(int val);

    // bool avoidObstacles(float lowerLeftData[], float upperLeftData[], float lowerRightData[], float upperRightData[]);
    bool avoidObstacles(float leftData[], float rightData[]);

    void DisplayObsDistances(float leftValue, float rightValue);

    bool runningBackwards();
    bool swivelRight120();
    bool swivelLeft120();
    
    bool turningRight120();
    bool turningLeft120();
    
    bool turningRight60();
    bool turningLeft60();

    unsigned long _cn = 0;

    String displayText;
    
public:
    CarController(int servoPin, MotorPins lPins, MotorPins rPins): display(0x27, 16, 2){
        chassis = new ChassisController(lPins, rPins);
        turret = new TurretController(servoPin);
    }

    void init(){        
        chassis->init();
        turret->init();

        lr.init();
        display.init();
    }

    void drive(int velocity);

    void DisplayVelocityAndDistance(int velocity);

    void drive();
    int orientObstacle();
};
