#include "TurretController.h"
#include "ChassisController.h"
#include "UltrasonicController.h"
#include "DisplayControl.h"
#include <Arduino.h>

class CarController
{
private:
    TurretController *turret = nullptr;
    ChassisController *chassis = nullptr;    
    DisplayControl display;

    bool inFrontOfObstacle = false;

    bool detectObstacles();
    int detectionRange = 400;
   
    unsigned long lastTime = 0;
  
    bool hasObstacles(int val);

    bool avoidObstacles(float leftData[], float rightData[]);

    bool runningBackwards();
    bool swivelRight();
    bool swivelLeft();
    bool turningRight();
    bool turningLeft();

    String displayText;
    
public:
    CarController(int servoPin, MotorPins lPins, MotorPins rPins): display(0x27, 16, 2){
        chassis = new ChassisController(lPins, rPins);
        turret = new TurretController(servoPin);
        
    }

    void init(){        
        chassis->init();
        turret->init();

        display.init();
    }

    void drive(int velocity);
    

    void drive();
    int orientObstacle();
};
