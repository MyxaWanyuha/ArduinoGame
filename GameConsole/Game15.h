#ifndef GAME15_H
#define GAME15_H
#include <Arduino.h> // for random() in MixMap

struct Point
{
  Point( int x, int y )
    : x( x ), y( y ) {};
  int x, y;
};

class Game
{
public:
  Game();
  static constexpr int8_t width = 3;
  int8_t GetCellValue( int x, int y ) const { return map[x * width + y]; }
  uint16_t GetStepCount() const { return stepCount; }
protected:
  void MixMap();
  void MoveRight();
  void MoveLeft();
  void MoveUp();
  void MoveDown();
  bool IsWin() const;

private:
  int8_t map[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int8_t* GetCellPtr( int x, int y ) const { return map + y * width + x; }
  Point FindPlayer() const;
  void Swap( int8_t& p1, int8_t& p2 );
  uint16_t stepCount = 0;
};

#endif // GAME15_H
