#include <Arduino.h>
#include "Menu.h"

Menu m;
Game15Arduino j;
void setup()
{
  Graphics.begin(); 
}

uint64_t UpdateNext = 0;

void loop()
{
  Graphics.firstPage();
  do
  {
     m.MainUpdate();
  } 
  while( Graphics.nextPage() );
}
