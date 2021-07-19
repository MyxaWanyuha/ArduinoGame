#include "GamePrototype.h"

struct MenuGame
{
  MenuGame( const char* gameName, GamePrototype* (*game)())
    : gameName( gameName ), GetNewGame( game ) {}
  const char* gameName;
  GamePrototype* (*GetNewGame)();
};
