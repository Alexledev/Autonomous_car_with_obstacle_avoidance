#include <Arduino.h>
#include <math.h>

#ifndef UTIL_H
#define UTIL_H

class Utilities
{

    public:
        Utilities();

        static float mean(float arr[], int size)
        {
            float sum = 0;
            for (int i = 0; i < size; i++)
                sum += arr[i];
            return sum / size;
        }

        static float standardDeviation(float arr[], int size, float m)
        {
            float sumSq = 0;
            for (int i = 0; i < size; i++)
            {
                sumSq += pow(arr[i] - m, 2);
            }
            return sqrt(sumSq / size);
        }

        // Filters values within zThreshold * std from mean
        static int removeOutliers(float arr[], int size, float result[], float zThreshold = 3.0)
        {
            float m = mean(arr, size);
            float std = standardDeviation(arr, size, m);
            int count = 0;
            for (int i = 0; i < size; i++)
            {
                if (fabs(arr[i] - m) <= zThreshold * std)
                {
                    result[count++] = arr[i];
                }
            }
          
            return count; // number of elements after filtering
        }

        static int cleanData(float arr[], float* result)
        {
           
            int count = Utilities::removeOutliers(arr, 30, result);

            // Serial.print("Data after removed outliers: ");
            // printArr(result, 30);

            return count;
        }

        static void printArr(float data[], int length)
        {
            Serial.print("arr[");
            for (int i = 0; i < length; i++)
            {          
                Serial.print(data[i]);
                Serial.print(", ");
            }   
            Serial.println("]");
        };

        static float median3(float a, float b, float c) 
        {
            if ((a >= b && a <= c) || (a <= b && a >= c)) return a;
            if ((b >= a && b <= c) || (b <= a && b >= c)) return b;
            return c;
        }

};


#endif