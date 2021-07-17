#ifndef SNAKE_ARDUINO_H
#define SNAKE_ARDUINO_H

#include "Snake.h"
#include "GamePrototype.h"

class SnakeArduino : public GamePrototype, protected Snake
{
  void DrawBorder()
  {
    for( uint8_t i = 0; i < width; ++i )
    {
      Graphics.drawPixel( i, UpBorder );
      Graphics.drawPixel( i, DownBorder );
      Graphics.drawPixel( i, DownBorder + 1 );
    }
    for( uint8_t i = UpBorder; i < height; ++i )
    {
      Graphics.drawPixel( LeftBorder, i );
      Graphics.drawPixel( RightBorder, i );
      Graphics.drawPixel( LeftBorder - 1, i );
      Graphics.drawPixel( RightBorder + 1, i );
    }
  }

  void DrawSnake()
  {
  const auto snakeSize = GetSnakeSize();
    for( uint8_t z = 0; z < snakeSize; ++z )
    {
      const Point snakeSegment = GetSnakeSegmentCoordinates(z);
      for( uint8_t i = 0; i < snakeSize; ++i )
       Graphics.drawPixel( snakeSegment.x, snakeSegment.y );
    }
  }

  void DrawFood()
  {
    for( uint8_t i = 0; i < foodCount; ++i )
    {
      const Point foodCoord = GetFoodCoordinates(i);
      Graphics.drawPixel( foodCoord.x, foodCoord.y );
    }
  }
  
  virtual void Render() override
  {
    if( Mode == GameMode::Game )
    {
      DrawBorder();
      DrawSnake();
      DrawFood();

      Graphics.setFont( u8g2_font_ncenB08_tr );
      const char* text = "Points: ";
      TextHeightWidth textHW(text);
      Graphics.drawStr( 0, textHW.height, text );
      char buf[5];
      constexpr int8_t notation = 10;
      itoa( GetPoints(), buf, notation );
      Graphics.drawStr( textHW.width, textHW.height, buf );
    }
    else if( Mode == GameMode::Ready )
    {
      DefaultGameReadyRender("Snake");
    }
    else if( Mode == GameMode::End || Mode == GameMode::Reset )
    {
      Graphics.setFont( u8g2_font_ncenB10_tr );
      Graphics.drawStr( 8, 24, "GameOver" );

      const char* text = "Points: ";
      TextHeightWidth textHW(text);
      Graphics.drawStr( 10, textHW.height + 30, text );
      char buf[5];
      constexpr int8_t notation = 10;
      itoa( GetPoints(), buf, notation );
      Graphics.drawStr( textHW.width + 10, textHW.height + 30, buf );
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
