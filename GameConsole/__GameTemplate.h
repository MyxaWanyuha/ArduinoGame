#ifndef GAMENAME_ARDUINO_H
#define GAMENAME_ARDUINO_H

#include "GameName.h"
#include "GamePrototype.h"

class GameNameArduino : public GamePrototype, protected GameName
{
  // draw with Graphics
  virtual void Render() override
  {
    if( Mode == GameMode::Game )
    {
      
    }
    else if( Mode == GameMode::Ready )
    {
      DefaultGameReadyRender("GameName");
    }
    else if( Mode == GameMode::End || Mode == GameMode::Reset )
    {
      Graphics.setFont( u8g2_font_ncenB10_tr );
      Graphics.drawStr( 8, 24, "GameOver" );
    }
  }

  // control game mode and check controls
  virtual void Update() override
  { 
    if( ButtonUp )
      ;
    else if ( ButtonDown )
      ;
    else if ( ButtonLeft )
      ;
    else if ( ButtonRight )
      ;
    else if ( ButtonLeftUp )
      ;
    else if ( ButtonRightUp )
      ;
    if( /*GameOver()*/ )
      Mode = GameMode::End;
  }

  // reset your game parameters
  virtual void ResetGame() override
  {
  }
};

#endif // GAMENAME_ARDUINO_H
