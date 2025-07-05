#include <Arduino.h>
#include <DCMotorController.h>
#include <ChassisController.h>


MotorPins lMotor = {7, 6, 5};
MotorPins rMotor = {9, 8, 10};

ChassisController Chassis(lMotor, rMotor);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("forward");
  Chassis.forward(150);
  delay(2000);
  Serial.println("stop");
  Chassis.stop();
  delay(2000);
  Serial.println("backward");
  Chassis.backward(150);
  delay(2000);
  Serial.println("turnLeftAxial");
  Chassis.turnLeftAxial(150);
  delay(2000);
  Serial.println("turnRightAxial");
  Chassis.turnRightAxial(150);
  delay(2000);
  Serial.println("turnLeftRadial");
  Chassis.turnLeftRadial(150);
  delay(2000);
  Serial.println("turnRightRadial");
  Chassis.turnRightRadial(150);
  delay(2000);
}