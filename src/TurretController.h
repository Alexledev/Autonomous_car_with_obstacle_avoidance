#include <Servo.h>
#include <UltrasonicController.h>
#include <Arduino.h>

enum TurretDirections {
    MIDDLE,
    RIGHT,
    LEFT
};

struct TurretValue
{
    TurretDirections direction;
    unsigned int value;
};


class TurretController
{
private:
    Servo swivelMotor;
    UltrasonicController ultraSensor;

    unsigned long lastMoveTime=0;
    int sPin;
    int pos = 0;
    const int FORWARDALIGN = 90;    
    unsigned int currentSensorValue = 0;

    void turnLeft(int endDegrees);

public:
    TurretController(int servoPin): sPin(servoPin), ultraSensor(A0){
        
    }

    void init();
    void lookForward();
    void scan(int startDegrees, int endDegrees);
    void scan(int range);
    TurretValue getViewData(int range);

};
