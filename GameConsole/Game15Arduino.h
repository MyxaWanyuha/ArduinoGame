#ifndef GAME15_ARDUINO_H
#define GAME15_ARDUINO_H

#include "Game15.h"
#include "GamePrototype.h"

class Game15Arduino : protected Game, public GamePrototype
{
  virtual void Render() override
  {
    if( mode == GameMode::Game )
    {
      constexpr int8_t notation = 10;
      Graphics.setFont( u8g2_font_ncenB14_tr );
      for( int x = 0; x < width; ++x )
        for( int y = 0; y < width; ++y )
        {
          const auto cellValue = GetCellValue( y, x );
          char buf[2];
          itoa( cellValue, buf, notation );
          const TextHeightWidth textHW( buf );
          if( cellValue != width * width )
            Graphics.drawStr( textHW.width * x * 2, textHW.height * ( y + 1 ), buf );
        }

      const auto stepCount = GetStepCount();
      if(stepCount < 1000)
      {
        Graphics.setFont( u8g2_font_ncenB10_tr );
        char buf[5];
        itoa( stepCount, buf, notation );
        const TextHeightWidth textHW( buf );

        const char* steps = "steps: ";
        const TextHeightWidth stepsHW( steps );
        Graphics.drawStr( ScreenWidth - ( stepsHW.width + textHW.width ), stepsHW.height, steps );
        Graphics.drawStr( ScreenWidth - textHW.width, textHW.height, buf );
      }
    }
    else if( mode == GameMode::Ready )
    {
      DefaultGameReadyRender("15");
    }
    else if( mode == GameMode::End || mode == GameMode::Reset )
    {
      Graphics.setFont( u8g2_font_ncenB10_tr );
      Graphics.drawStr( 8, 24, "You win!" );
    }
  }

  virtual void Update() override
  { 
    if( buttonUp && MoveUp() )
      soundManager.Beep();
    else if ( buttonDown && MoveDown() )
      soundManager.Beep();
    else if ( buttonLeft && MoveLeft() )
      soundManager.Beep();
    else if ( buttonRight && MoveRight() )
      soundManager.Beep();

    if( IsWin() )
      mode = GameMode::End;
	}

  virtual void ResetGame() override
  {
    MixMap();
  }
};

#endif // GAME15_ARDUINO_H
