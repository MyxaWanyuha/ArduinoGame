#include <Arduino.h>
#include "Game15Arduino.h"
#include "SnakeArduino.h"

//Game15Arduino g;
//SnakeArduino game;

GamePrototype* game = nullptr;

void setup()
{
  Graphics.begin();
  game = new SnakeArduino();
}

void loop()
{
  game->UpdateGame();
}
