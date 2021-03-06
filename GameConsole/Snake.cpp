#include  "Snake.h"

Snake::Snake()
{
  Reset();
}

void Snake::Reset()
{
  snakeSize = 1;
  snake[0] = Point( width / 2, height / 2);
  for( uint8_t i = 0; i < foodCount; ++i )
   ReplaceFood(i);
  snakeSpeed = defaultSnakeSpeed;
  points = 0;
}

bool Snake::MoveSnakeAndCheckIntersection()
{
  const Point head = Point(
    snake[0].x + static_cast<int8_t>( xDir ),
    snake[0].y + static_cast<int8_t>( yDir ) );

  //move tail
  for ( auto i = snakeSize; i != 0; --i )
  {
    snake[i] = snake[i - 1];

    // check snake self intersection
    if ( head.x == snake[i - 1].x && head.y == snake[i - 1].y )
      return true;
  }

  snake[0] = head;

  if ( snake[0].x == LeftBorder - 1
    || snake[0].x == RightBorder + 1
    || snake[0].y == DownBorder - 1 
    || snake[0].y == UpBorder + 1 )
    return true;
  return false;
}

bool Snake::IsFoodEaten()
{
  const int8_t food = GetEatenFoodIndex();
  if( food >= 0 )
  {
    ReplaceFood( food );
    ++snakeSize;
    ++points;
   
    // speed up snake
    snakeSpeed = 100 - 20 * ( snakeSize >> 2 );
    if( snakeSpeed >= 3 )
      snakeSpeed -= 3;
    else
      snakeSpeed = 0;
    return true;
  }
  return false;
}

void Snake::ReplaceFood(uint8_t i)
{
  food[i].x = random( LeftBorder + 1, RightBorder - 1 );
  food[i].y = random( UpBorder + 1, DownBorder - 1 );
}

int8_t Snake::GetEatenFoodIndex() const
{
  for( uint8_t i = 0; i < foodCount; ++i )
    if( snake[0].x == food[i].x && snake[0].y == food[i].y )
      return i;
  return -1;
}

void Snake::MoveUp()
{
  if ( yDir == Direction::Down ) return;
  xDir = Direction::None;
  yDir = Direction::Up;
}

void Snake::MoveDown()
{
  if ( yDir == Direction::Up ) return;
  xDir = Direction::None;
  yDir = Direction::Down;
}

void Snake::MoveRight()
{
  if ( xDir == Direction::Left ) return;
  xDir = Direction::Right;
  yDir = Direction::None;
}

void Snake::MoveLeft()
{
  if ( xDir == Direction::Right ) return;
  xDir = Direction::Left;
  yDir = Direction::None;
}
