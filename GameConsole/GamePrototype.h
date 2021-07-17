#ifndef GAME_PROTOTYPE_H
#define GAME_PROTOTYPE_H

#include "Sound.h"
#include "Graphics.h"

enum class GameMode : uint8_t
{
  Game = 0,
  End,
  Reset,
  Ready
};

enum class PinButton : uint8_t
{
  Up = A0,
  Down = A1,
  Left = A2,
  Right = A3,
  RightUp = 4,
  LeftUp = 7
};

class GamePrototype
{
public:
  void UpdateGame();

protected:
  virtual void Render() = 0;
  virtual void Update() = 0;
  virtual void ResetGame() = 0;
  
  void DefaultGameReadyRender(const char* GameName);
  
  GameMode Mode = GameMode::Ready;

  bool ButtonUp = false;
  bool ButtonDown = false;
  bool ButtonLeft = false;
  bool ButtonRight = false;
  bool ButtonRightUp = false;
  bool ButtonLeftUp = false;
  
  bool isIntro = true;
  
private:
  virtual void PlaySound();

  void GraphicsRender();
  
  uint64_t ControlNext = 0;
  uint64_t UpdateNext = 0;
  uint64_t ResetNext = 0;
  uint64_t PlayNext = 0;
  uint64_t IntroNext = 0;

  const uint16_t UpdateTimeout = 100;
  const uint16_t ResetTimeout = 2000;
  const uint8_t ControlTimeout = 10;
  const uint8_t BeepTimeout = 100;
  const uint16_t IntroTimeout = 500;
};

#endif // GAME_PROTOTYPE_H
