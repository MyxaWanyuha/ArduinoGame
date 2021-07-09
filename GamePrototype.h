#ifndef GAME_PROTOTYPE_H
#define GAME_PROTOTYPE_H

#include "Sound.h"

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
	void UpdateGame()
	{
    PlaySound();

    uint64_t time = millis();

    if( Mode == GameMode::End )
    {
        ResetNext = time + ResetTimeout;
        Mode = GameMode::Reset;
    }

    if( Mode == GameMode::Reset && time > ResetNext )
      ResetGame();

    if( Mode == GameMode::Ready && time > IntroNext )
    {
      IntroNext = time + IntroTimeout;
      intro_state = !intro_state;
    }

    //UpdateControls
    if(( Mode == GameMode::Ready || Mode == GameMode::Game ) && time > ControlNext )
    {
      ControlNext = time + ControlTimeout;

      ButtonUp = digitalRead(static_cast<uint8_t>(PinButton::Up));
      ButtonDown = digitalRead(static_cast<uint8_t>(PinButton::Down));
      ButtonLeft = digitalRead(static_cast<uint8_t>(PinButton::Left));
      ButtonRight = digitalRead(static_cast<uint8_t>(PinButton::Right));
      ButtonRightUp = digitalRead(static_cast<uint8_t>(PinButton::RightUp));
      ButtonLeftUp = digitalRead(static_cast<uint8_t>(PinButton::LeftUp));

      if( Mode == GameMode::Ready && ( ButtonUp || ButtonDown || ButtonLeft || ButtonRight || ButtonRightUp || ButtonLeftUp ) )
        Mode = GameMode::Game;
    }
    else
    {
        ButtonUp = false;
        ButtonDown = false;
        ButtonLeft = false;
        ButtonRight = false;
        ButtonRightUp = false;
        ButtonLeftUp = false;
    }

    if( Mode == GameMode::Game && time > UpdateNext )
        UpdateNext = time + UpdateTimeout;

    //Update game state
    Update();

    //Draw game
    GraphicsRender();
  }

protected:
  virtual void PlaySound()
  {
    if( Mode == GameMode::Ready )
      soundManager.PlayMelody(MelodyID::Intro, true);
    else if( Mode == GameMode::Reset )
      soundManager.PlayMelody(MelodyID::GameOver, false);
    else if( Mode == GameMode::Game )
      soundManager.PlayMelody(MelodyID::GameStart, false);
  }
  
  void GraphicsRender()
  {
    Graphics.firstPage();
    do
    {
        Render();
    } 
    while( Graphics.nextPage() );
  }
  
  virtual void Render() = 0;
  virtual void Update() = 0;
  virtual void ResetGame() = 0;
  bool ButtonUp = false;
  bool ButtonDown = false;
  bool ButtonLeft = false;
  bool ButtonRight = false;
  bool ButtonRightUp = false;
  bool ButtonLeftUp = false;

  uint64_t ControlNext = 0;
  uint64_t UpdateNext = 0;
  uint64_t ResetNext = 0;
  uint64_t PlayNext = 0;
  uint64_t IntroNext = 0;

  const uint16_t UpdateTimeout = 200;
  
  GameMode Mode = GameMode::Ready;

  const uint16_t ResetTimeout = 5000;
  const uint8_t ControlTimeout = 100;
  const uint8_t BeepTimeout = 100;
  const uint16_t IntroTimeout = 500;

  bool intro_state = true;

  SoundManager soundManager;
};

#endif // GAME_PROTOTYPE_H
