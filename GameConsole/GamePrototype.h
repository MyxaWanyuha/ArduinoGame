#ifndef GAME_PROTOTYPE_H
#define GAME_PROTOTYPE_H

#include "Sound.h"
#include "Graphics.h"

enum class PinButton : uint8_t
{
  Up = A0,
  Down = A1,
  Left = A2,
  Right = A3,
  RightUp = 4,
  LeftUp = 7,
};

class GamePrototype
{
public:
  virtual ~GamePrototype(){}
  
  void UpdateGame()
  {
    PlaySound();

    const uint64_t time = millis();

    if( mode == GameMode::End )
    {
      resetNext = time + ResetTimeout;
      mode = GameMode::Reset;
    }

    if( mode == GameMode::Reset && time > resetNext )
    {
      mode = GameMode::Ready;
      ResetGame();
    }
    if( mode == GameMode::Ready && time > introNext )
    {
      introNext = time + IntroTimeout;
      isIntro = !isIntro;
    }

    //UpdateControls
    if( ( mode == GameMode::Ready || mode == GameMode::Game ) && time > controlNext )
    {
      controlNext = time + ControlTimeout;

      buttonUp = digitalRead( static_cast<uint8_t>( PinButton::Up ) );
      buttonDown = digitalRead( static_cast<uint8_t>( PinButton::Down ) );
      buttonLeft = digitalRead( static_cast<uint8_t>( PinButton::Left ) );
      buttonRight = digitalRead( static_cast<uint8_t>( PinButton::Right ) );
      buttonRightUp = digitalRead( static_cast<uint8_t>( PinButton::RightUp ) );
      buttonLeftUp = digitalRead( static_cast<uint8_t>( PinButton::LeftUp ) );

      if( mode == GameMode::Ready && ( buttonUp || buttonDown || buttonLeft || buttonRight || buttonRightUp || buttonLeftUp ) )
        mode = GameMode::Game;
    }
    else
    {
      buttonUp = false;
      buttonDown = false;
      buttonLeft = false;
      buttonRight = false;
      buttonRightUp = false;
      buttonLeftUp = false;
    }

    if( mode == GameMode::Game && time > updateNext )
    {
      updateNext = time + updateTimeout;
      //Update game state
      Update();
    }
    //Draw game
    GraphicsRender();
  }

protected:
  enum class GameMode : uint8_t
  {
    Game = 0,
    End,
    Reset,
    Ready
  };

  void DefaultGameReadyRender(const char* gameName, const char* creator = "github MyxaWanyuha")
  {
    Graphics.setFont( u8g2_font_ncenB08_tr );
    Graphics.drawStr( 0, 24, creator );
    Graphics.setFont( u8g2_font_ncenB10_tr );
    Graphics.drawStr( 20, 40, gameName );
    Graphics.setFont( u8g2_font_ncenB08_tr );
    const char* text = "Press any key";
    
    TextHeightWidth textHW(text);
    if( isIntro )
      Graphics.drawStr( 10, 55, text );
    else
      Graphics.drawBox( 10, 55 - textHW.height, textHW.width, textHW.height ); // remove text
  }

  GameMode mode = GameMode::Ready;

  virtual void Render() = 0;
  virtual void Update() = 0;
  virtual void ResetGame() = 0;
  
  bool buttonUp = false;
  bool buttonDown = false;
  bool buttonLeft = false;
  bool buttonRight = false;
  bool buttonRightUp = false;
  bool buttonLeftUp = false;
  
  bool isIntro = true;
  const uint16_t defaultUpdateTimeout = 100;
  uint16_t updateTimeout = defaultUpdateTimeout;
private:
  virtual void PlaySound()
  {
    if( mode == GameMode::Ready )
      soundManager.PlayMelody( MelodyID::Intro, true );
    else if( mode == GameMode::End || mode == GameMode::Reset )
      soundManager.PlayMelody( MelodyID::GameOver );
    else if( mode == GameMode::Game )
      soundManager.PlayMelody( MelodyID::GameStart );
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

  uint64_t controlNext = 0;
  uint64_t updateNext = 0;
  uint64_t resetNext = 0;
  uint64_t playNext = 0;
  uint64_t introNext = 0;
  
  const uint16_t ResetTimeout = 2000;
  const uint8_t ControlTimeout = 10;
  const uint8_t BeepTimeout = 100;
  const uint16_t IntroTimeout = 500;
};

#endif // GAME_PROTOTYPE_H
