#include <Arduino.h>
#include "Game15Arduino.h"
#include "SnakeArduino.h"

SnakeArduino game;

void setup()
{
  Graphics.begin(); 
}

void loop()
{
  game.UpdateGame();
}
