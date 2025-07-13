#include <Arduino.h>
#include <CarController.h>

MotorPins lMotor = {7, 6, 5};
MotorPins rMotor = {12, 8, 11}; // 9 and 10 are taken by the Timer on the Servo motors

const int turretPin = 2;

CarController carControl(turretPin, lMotor, rMotor);

void setup()
{
  Serial.begin(9600);
  carControl.init();
}

void loop()
{ 
  carControl.drive(140);
}
