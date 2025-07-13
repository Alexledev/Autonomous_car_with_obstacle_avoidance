
#include "DisplayControl.h"
#include "Arduino.h"

void DisplayControl::displayLine(int row, String text, bool clear=false)
{   
    if (clear == true)
    {        
      unsigned long currentTime = millis();
      if (currentTime - prevTime > displayInterval)
      {
        lcd->clear();  
        prevTime = currentTime;
      }    
    }

    lcd->setCursor(0,row);
    lcd->print(text);
   
}