#ifndef GAMENAME_ARDUINO_H
#define GAMENAME_ARDUINO_H

#include "GameName.h"
#include "GamePrototype.h"

class GameNameArduino : public GamePrototype, protected GameName
{
  // draw with Graphics
  virtual void Render() override
  {
    if( mode == GameMode::Game )
    {
      
    }
    else if( mode == GameMode::Ready )
    {
      DefaultGameReadyRender("GameName");
    }
    else if( mode == GameMode::End || mode == GameMode::Reset )
    {
      Graphics.setFont( u8g2_font_ncenB10_tr );
      Graphics.drawStr( 8, 24, "GameOver" );
    }
  }

  // control game mode and check controls
  virtual void Update() override
  { 
    if( buttonUp )
      ;
    else if ( buttonDown )
      ;
    else if ( buttonLeft )
      ;
    else if ( buttonRight )
      ;
    else if ( buttonLeftUp )
      ;
    else if ( buttonRightUp )
      ;
    if( /*GameOver()*/ )
      mode = GameMode::End;
  }

  // reset your game parameters
  virtual void ResetGame() override
  {
  }
};

#endif // GAMENAME_ARDUINO_H
