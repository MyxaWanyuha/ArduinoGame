#include "GamePrototype.h"

void GamePrototype::UpdateGame()
{
  PlaySound();

  const auto time = millis();

  if( Mode == GameMode::End )
  {
    ResetNext = time + ResetTimeout;
    Mode = GameMode::Reset;
  }

  if( Mode == GameMode::Reset && time > ResetNext )
  {
    Mode = GameMode::Ready;
    ResetGame();
  }
  if( Mode == GameMode::Ready && time > IntroNext )
  {
    IntroNext = time + IntroTimeout;
    isIntro = !isIntro;
  }

  //UpdateControls
  if( ( Mode == GameMode::Ready || Mode == GameMode::Game ) && time > ControlNext )
  {
    ControlNext = time + ControlTimeout;

    ButtonUp = digitalRead( static_cast<uint8_t>( PinButton::Up ) );
    ButtonDown = digitalRead( static_cast<uint8_t>( PinButton::Down ) );
    ButtonLeft = digitalRead( static_cast<uint8_t>( PinButton::Left ) );
    ButtonRight = digitalRead( static_cast<uint8_t>( PinButton::Right ) );
    ButtonRightUp = digitalRead( static_cast<uint8_t>( PinButton::RightUp ) );
    ButtonLeftUp = digitalRead( static_cast<uint8_t>( PinButton::LeftUp ) );

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
  {
    UpdateNext = time + UpdateTimeout;
    //Update game state
    Update();
  }
  //Draw game
  GraphicsRender();
}

void GamePrototype::DefaultGameReadyRender(const char* GameName)
{
  Graphics.setFont( u8g2_font_ncenB10_tr );
  Graphics.drawStr( 6, 24, "MyxaWanyuha" );
  Graphics.drawStr( 20, 40, GameName );
  Graphics.setFont( u8g2_font_ncenB08_tr );
  const char* text = "Press any key";
    
  TextHeightWidth textHW(text);
  if( isIntro )
    Graphics.drawStr( 10, 55, text );
  else
    Graphics.drawBox( 10, 55 - textHW.height, textHW.width, textHW.height ); // remove text
}

void GamePrototype::PlaySound()
{
  if( Mode == GameMode::Ready )
    soundManager.PlayMelody( MelodyID::Intro, true );
  else if( Mode == GameMode::End )
    soundManager.PlayMelody( MelodyID::GameOver );
  else if( Mode == GameMode::Game )
    soundManager.PlayMelody( MelodyID::GameStart );
}

void GamePrototype::GraphicsRender()
{
  Graphics.firstPage();
  do
  {
    Render();
  } 
  while( Graphics.nextPage() );
}

