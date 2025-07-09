
#include "DisplayControl.h"
#include "Arduino.h"

void DisplayControl::displayLine(int row, String text, bool clear=false)
{   
    if (clear == true)
    {        
      unsigned long currentTime = millis();
      prevTime = currentTime;
      while (currentTime - prevTime < displayInterval)
      {
        currentTime = millis();
      }
    
      lcd->clear();  
    }

    lcd->setCursor(0,row);
    lcd->print(text);
   
}