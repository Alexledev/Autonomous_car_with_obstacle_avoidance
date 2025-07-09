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

    int detectionTimeframe = 20;
    unsigned long lastTime = 0;
    int obstacleDir = -2;

    bool detectedLast = false;
    bool hasObstacles(int val);

    bool avoidObstacles(unsigned int leftValue, unsigned int rightValue);

    bool runningBackwards();
    bool swivelRight();
    bool swivelLeft();
    bool turningRight();
    bool turningLeft();

    String displayText;

    
    // Directions currentDir;

    void printArr(unsigned int data[], int length)
    {
        Serial.print("arr[");
        for (int i = 0; i < length; i++)
        {          
            Serial.print(data[i]);
            Serial.print(", ");
        }   
         Serial.println("]");
    };

    unsigned int* sortArray(unsigned int a[], int size) 
    {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (a[j] > a[j + 1]) {
                    int temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                }
            }
        }

        return a;
    }    

    unsigned int* filterBelow(unsigned int data[], int dataSize, int threshold, int &refCount)
    {
        unsigned int tcount;
        Serial.print("filterred[");
        for (int index = 0; index < dataSize; index++)
        {
            if (data[index] > threshold && data[index] < 200){
                Serial.print(data[index]);
                Serial.print(", ");
                tcount++;
            }
        }
        Serial.println("]");
        
        // Serial.print("tCount: ");
        // Serial.println(tcount);

        unsigned int returnList[tcount];
        // int i=0;
        // for (int index = 0; index < dataSize; index++)
        // {
        //     if (data[index] > threshold){
        //         returnList[index] = data[index];
        //     }
        // }

        // refCount = tcount;
        return returnList;
    }

    int getMedian(unsigned int data[], int size)
    {
        int _size = 0;
        unsigned int* sorted =  sortArray(data, size);
        printArr(sorted, size);
        unsigned int* arr = filterBelow(sorted, size, 40, _size); //filterOutBelow(sortArray(data, size), size, 40, &_size);  // Sort in-place
        // printArr(arr, _size);

        // Serial.print("_size: ");
        // Serial.println(_size);

        if (_size % 2 == 1) {
            return arr[_size / 2];  // Odd length
        } else {
            return (arr[_size / 2 - 1] + arr[_size / 2]) / 2.0;  // Even length
        }
    };

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
