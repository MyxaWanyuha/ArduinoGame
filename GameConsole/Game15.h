#ifndef GAME15_H
#define GAME15_H
#include <Arduino.h> // for random() in MixMap

class Game
{
public:
  Game();
  static constexpr int8_t width = 3;
  int8_t GetCellValue( int x, int y ) const { return map[x * width + y]; }
  uint16_t GetStepCount() const { return stepCount; }
protected:
  void MixMap();
  bool MoveRight();
  bool MoveLeft();
  bool MoveUp();
  bool MoveDown();
  bool IsWin() const;

private:
  int8_t map[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int8_t* GetCellPtr( int x, int y ) const { return map + y * width + x; }
  void Swap( int8_t& p1, int8_t& p2 );
  uint16_t stepCount = 0;
  uint8_t pointX = width - 1;
  uint8_t pointY = width - 1;
};

#endif // GAME15_H
