#include "Game15.h"

Game::Game()
{
  MixMap();
}

bool Game::MoveRight()
{
  if ( pointX < width - 1 )
  {
    Swap( *GetCellPtr( pointX, pointY ), *GetCellPtr( pointX + 1, pointY ) );
    ++pointX;
    return true;
  }
  return false;
}

bool Game::MoveLeft()
{
  if ( pointX > 0 )
  {
    Swap( *GetCellPtr( pointX, pointY ), *GetCellPtr( pointX - 1, pointY ) );
    --pointX;
    return true;
  }
  return false;
}

bool Game::MoveUp()
{
  if ( pointY > 0 )
  {
    Swap( *GetCellPtr( pointX, pointY ), *GetCellPtr( pointX, pointY - 1 ) );
    --pointY;
    return true;
  }
  return false;
}

bool Game::MoveDown()
{
  if ( pointY < width - 1 )
  {
    Swap( *GetCellPtr( pointX, pointY ), *GetCellPtr( pointX, pointY + 1 ) );
    ++pointY;
    return true;
  }
  return false;
}

bool Game::IsWin() const
{
  for ( int i = 0; i < width * width - 1; i++ )
    if ( map[i] > map[i + 1] )
      return false;
  return true;
}

void Game::Swap( int8_t& p1, int8_t& p2 )
{
  ++stepCount;
  p1 ^= p2 ^= p1 ^= p2;
}

void Game::MixMap()
{
  for ( int n = 0; n < 500; n++ )
  {
    const int com = random( 4 );
    if ( com == 0 )
      MoveRight();
    else if ( com == 1 )
      MoveLeft();
    else if ( com == 2 )
      MoveUp();
    else if ( com == 3 )
      MoveDown();
  }
  stepCount = 0;
}
