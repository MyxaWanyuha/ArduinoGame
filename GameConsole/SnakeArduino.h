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
    for( uint8_t i = 0; i < snakeSize; ++i )
    {
      const Point snakeSegment = GetSnakeSegmentCoordinates( i );
      for( uint8_t j = 0; j < snakeSize; ++j )
       Graphics.drawPixel( snakeSegment.x, snakeSegment.y );
    }
  }

  void DrawFood()
  {
    for( uint8_t i = 0; i < foodCount; ++i )
    {
      const Point foodCoord = GetFoodCoordinates( i );
      Graphics.drawPixel( foodCoord.x, foodCoord.y );
    }
  }
  
  virtual void Render() override
  {
    if( mode == GameMode::Game )
    {
      DrawBorder();
      DrawSnake();
      DrawFood();

      Graphics.setFont( u8g2_font_ncenB08_tr );
      const char* text = "Points: ";
      const TextHeightWidth textHW(text);
      Graphics.drawStr( 0, textHW.height, text );
      char buf[5];
      constexpr int8_t notation = 10;
      itoa( GetPoints(), buf, notation );
      Graphics.drawStr( textHW.width, textHW.height, buf );
    }
    else if( mode == GameMode::Ready )
    {
      DefaultGameReadyRender("Snake");
    }
    else if( mode == GameMode::End || mode == GameMode::Reset )
    {
      Graphics.setFont( u8g2_font_ncenB10_tr );
      Graphics.drawStr( 8, 24, "GameOver" );

      const char* text = "Points: ";
      const TextHeightWidth textHW(text);
      Graphics.drawStr( 10, textHW.height + 30, text );
      char buf[5];
      constexpr int8_t notation = 10;
      itoa( GetPoints(), buf, notation );
      Graphics.drawStr( textHW.width + 10, textHW.height + 30, buf );
    }
  }

  virtual void Update() override
  { 
    if( buttonUp )
      MoveUp();
    else if ( buttonDown )
      MoveDown();
    else if ( buttonLeft )
      MoveLeft();
    else if ( buttonRight )
      MoveRight();
    
    if( MoveSnakeAndCheckIntersection() )
      mode = GameMode::End;

    if( IsFoodEaten() )
    {
      updateTimeout = GetSnakeSpeed();
      soundManager.Beep();
    }
  }

  virtual void ResetGame() override
  {
    Reset();
    updateTimeout = defaultUpdateTimeout;
  }
};

#endif // SNAKE_ARDUINO_H
