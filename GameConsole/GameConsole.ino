#include <Arduino.h>
#include "Menu.h"

Menu menu;

void setup()
{
  Graphics.begin(); 
}

void loop()
{
  menu.MainUpdate();
}
