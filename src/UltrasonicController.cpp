#include "UltrasonicController.h"
#include <Arduino.h>

unsigned int UltrasonicController::getValue() {
    // Example: Read analog value from the ultrasonic sensor pin and print it
    unsigned int value = analogRead(pin);
    return value;
}