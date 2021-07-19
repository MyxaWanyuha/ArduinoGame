#include "MenuGame.h"
#include "Game15Arduino.h"
#include "SnakeArduino.h"

static const MenuGame menuGames[] =
{
  MenuGame( "15", [] { return new Game15Arduino(); } ),
  MenuGame( "Snake", [] { return new SnakeArduino(); } ),
  MenuGame( "Tetris", [] { return new SnakeArduino(); } ),
  MenuGame( "Racing", [] { return new Game15Arduino(); } ),
  MenuGame( "Shooter", [] { return new SnakeArduino(); } ),
  MenuGame( "Space", [] { return new SnakeArduino(); } ),
};
