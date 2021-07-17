#ifndef SNAKE_H
#define SNAKE_H
#include <Arduino.h>

struct Point
{
  constexpr Point( uint8_t x, uint8_t y ) : x( x ), y( y ) {};
  Point(){};
  uint8_t x = 0;
  uint8_t y = 0;
};

class Snake
{
public:

  Snake();
  void Reset();
  bool MoveSnakeAndCheckIntersection();

  void ReplaceFood(uint8_t i);

  // return -1 if not eaten
  int8_t GetEatenFoodIndex();
  
  void MoveUp();
  void MoveDown();
  void MoveRight();
  void MoveLeft();
  
  static const uint8_t height = 64;
  static const uint8_t width = 128;
  static const uint8_t snakeMaxLength = width;
  
  uint8_t snakeSize = 1;  
  //uint8_t snakeX[snakeMaxLength] = { width / 2 };
  //uint8_t snakeY[snakeMaxLength] = { height / 2 };

  Point snake[snakeMaxLength];
  static const uint8_t foodCount = 5;
  Point food[foodCount];

  const uint8_t UpBorder = 16;
  const uint8_t DownBorder = height - 2;
  const uint8_t RightBorder = width - 2;
  const uint8_t LeftBorder = 1;
  
private:

  uint16_t points = 0;

  enum class Direction : int8_t 
  {
    None = 0,
    Up = -1,
    Right = 1,
    Down = 1,
    Left = -1
  };
  
  Direction xDir = Direction::Right;
  Direction yDir = Direction::None;
};

#endif // SNAKE_H
