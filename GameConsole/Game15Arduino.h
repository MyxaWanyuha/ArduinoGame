#ifndef GAME15_ARDUINO_H
#define GAME15_ARDUINO_H

#include "Game15.h"
#include "GamePrototype.h"

class Game15Arduino : protected Game, public GamePrototype
{
  virtual void Render() override
  {
    if( Mode == GameMode::Game )
    {
      Graphics.setFont( u8g2_font_ncenB14_tr );
      for( int x = 0; x < width; ++x )
        for( int y = 0; y < width; ++y )
        {
          auto cellValue = GetCellValue( y, x );
          char buf[5];
          constexpr int8_t notation = 10;
          itoa( cellValue, buf, notation );
          TextHeightWidth textHW(buf);
          if( cellValue != width * width )
            Graphics.drawStr( textHW.width * ( x + 1 ) * 2, textHW.height * ( y + 1 ), buf );
        }
    }
    else if( Mode == GameMode::Ready )
    {
      Graphics.setFont( u8g2_font_ncenB10_tr );
      Graphics.drawStr( 6, 24, "MyxaWanyuha" );
      Graphics.drawStr( 20, 40, "15" );

      Graphics.setFont( u8g2_font_ncenB08_tr );
      const char* text = "Press any key";
      TextHeightWidth textHW(text);
      if( intro_state )
        Graphics.drawStr( 10, 55, text );
      else
        Graphics.drawBox( 10, 55 - textHW.height, textHW.width, textHW.height ); // remove text
    }
    else if( Mode == GameMode::End || Mode == GameMode::Reset )
    {
      Graphics.setFont( u8g2_font_ncenB10_tr );
      Graphics.drawStr( 8, 24, "You win!" );
    }
  }

  virtual void Update() override
  { 
    if( ButtonUp )
      {
        MoveUp();
        soundManager.Beep();
      }
    else if ( ButtonDown )
      MoveDown();
    else if ( ButtonLeft )
      MoveLeft();
    else if ( ButtonRight )
      MoveRight();

    if( IsWin() )
      Mode = GameMode::End;
	}

  virtual void ResetGame() override
  {
    MixMap();
  }
};

#endif // GAME15_ARDUINO_H
