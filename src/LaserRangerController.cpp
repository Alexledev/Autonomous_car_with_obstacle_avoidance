#include "LaserRangerController.h"
#include "Utilities.h"

bool LaserRangerController::collectData()
{
    while (sensorData < arrLen)
    {
        // sensor.read
        arr[sensorData] = sensor.readRangeSingleMillimeters();
        sensorData++;
    }

    return true;
}


unsigned long LaserRangerController::getRangeInMM()
{
    unsigned long _sum = 0;
    for (int i = 1; i < arrLen - 1; i++)
    {
       _sum += Utilities::median3(arr[i - 1], arr[i], arr[i + 1]);      
    }
    sensorData = 0;
    return _sum/6;
}