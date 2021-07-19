#include <Arduino.h>
#include "Menu.h"

Menu m;

void setup()
{
  Graphics.begin(); 
}

void loop()
{
  m.MainUpdate();
}
