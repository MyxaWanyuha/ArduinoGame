#ifndef SNAKE_ARDUINO_H
#define SNAKE_ARDUINO_H

#include "Snake.h"
#include "GamePrototype.h"

class SnakeArduino : public GamePrototype, protected Snake
{
    virtual void Render() override
  {
    if( Mode == GameMode::Game )
    {
      //draw border
      for( uint8_t i = 0; i < width; ++i )
      {
        Graphics.drawPixel( i, UpBorder );
        Graphics.drawPixel( i, DownBorder );
        Graphics.drawPixel( i, DownBorder + 1 );
      }
      for( uint8_t i = 0; i < height; ++i )
      {
        Graphics.drawPixel( LeftBorder, i );
        Graphics.drawPixel( RightBorder, i );
        Graphics.drawPixel( LeftBorder - 1, i );
        Graphics.drawPixel( RightBorder + 1, i );
      }
      
      for( uint8_t z = 0; z < snakeSize; ++z )
      {
        const auto x = snake[z].x;
        const auto y = snake[z].y;
        if( snakeSize == 1 )
          Graphics.drawPixel( x, y );
        else
          for( uint8_t i = 0; i < snakeSize; ++i )
          {
            Graphics.drawPixel( x, y );
          }
      }
      for( uint8_t i = 0; i < foodCount; ++i )
      {
        Graphics.drawPixel( food[i].x, food[i].y );
      }
    }
    else if( Mode == GameMode::Ready )
    {
      Graphics.setFont( u8g2_font_ncenB10_tr );
      Graphics.drawStr( 6, 24, "MyxaWanyuha" );
      Graphics.drawStr( 20, 40, "Snake" );

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
      Graphics.drawStr( 8, 24, "GameOver" );
    }
  }

  virtual void Update() override
  { 
    if( ButtonUp )
      MoveUp();
    else if ( ButtonDown )
      MoveDown();
    else if ( ButtonLeft )
      MoveLeft();
    else if ( ButtonRight )
      MoveRight();
    
    if( MoveSnakeAndCheckIntersection() )
      Mode = GameMode::End;
  }

  virtual void ResetGame() override
  {
    Reset();
  }
};

#endif // SNAKE_ARDUINO_H
