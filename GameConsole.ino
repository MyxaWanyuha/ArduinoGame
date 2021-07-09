#include <Arduino.h>
#include "Game15Arduino.h"

Game15Arduino game;

void setup()
{
  Graphics.begin(); 
}

void loop()
{
  game.UpdateGame();
}
