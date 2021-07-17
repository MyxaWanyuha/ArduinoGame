#include <Arduino.h>
#include "Game15Arduino.h"
#include "SnakeArduino.h"

Game15Arduino g;
SnakeArduino game;

void setup()
{
  Graphics.begin(); 
}

void loop()
{
  g.UpdateGame();
}
