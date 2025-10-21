# Autonomous Car with Ultrasonic and Light-based obstacle avoidance

An Arduino-based car with an ultrasonic mounted on a rotating turret and a light sensor on the front, both of them helping the car to move around environments and avoid obstacle.
Demo: https://www.youtube.com/shorts/H-D1xPRFkRE

## Installation
1. Install platformIO on VSCode.
2. Install the following libraries:
   - arduino-libraries/Servo@^1.2.2
	 - marcoschwartz/LiquidCrystal_I2C@^1.1.4
	 - pololu/VL53L0X@^1.3.1
3. Upload the code onto the arduino (make sure to remove pins on TX and RX while uploading)

## Explanation/Usage
1. The car will move straight forward until the light sensor detects an obstacle within 450 mm (or so).
2. The car will stop and the turret will swivel back and forth, the Ultrasonic sensor will start scanning at around the edges.
3. From the observation results, there are several actions it can do (detection means that the obstacle is inside it's range):
   - Obstacles detected on only right: Car will move backwards a bit and turn left.
   - Obstacles detected on only left: Car will move backwards a bit and turn right. 
   - Obstacles detected on both sides but left is closer: Car swivels and orients itself to the right.
   - Obstacles detected on both sides but right is closer: Car swivels and orients itself to the left.
   - Obstacles not detected on both sides: Similar behaviour to when it sees obstacles on both sides
     
- You can use the POT to adjust the forward speed of the car.

## License
MIT License
