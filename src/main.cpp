#include <Arduino.h>
#include <DCMotorController.h>
#include <ChassisController.h>
#include <Servo.h>
#include <TurretController.h>
#include <UltrasonicController.h>
#include <CarController.h>
#include <DisplayControl.h>

MotorPins lMotor = {7, 6, 5};
MotorPins rMotor = {12, 8, 11}; // 9 and 10 are taken by the Timer on the Servo motors

const int turretPin = 2;

// const int encoderPWM = 3;
// unsigned int countA = 0;
// DisplayControl displayControl(0x27, 16, 2);

CarController carControl(turretPin, lMotor, rMotor);

void setup()
{
  Serial.begin(9600);
  carControl.init();
}

void loop()
{ 
  carControl.drive(140);
  // delay(10);   
}
