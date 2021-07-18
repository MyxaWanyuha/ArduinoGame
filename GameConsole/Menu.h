#ifndef MENU_H
#define MENU_H
#include <Arduino.h>
#include "GamePrototype.h"
#include "Game15Arduino.h"
#include "SnakeArduino.h"

class Menu
{
public:
  ~Menu()
  {
    delete( gameptr );
  }
  
  void MainUpdate()
  {
    Update();
    Render();
  }
  
protected:
  void Render()
  {
    if (gameptr != nullptr) return;
    
    Graphics.setFont( u8g2_font_ncenB10_tr );
    const TextHeightWidth stepsHW( names[0] );
    for( uint8_t i = 0; i < itemsCount; ++i )
    {
      Graphics.drawStr( 10, stepsHW.height * ( i + 1 ), names[i] );
    }
    const char* finger = "> ";
    Graphics.drawStr( 0, stepsHW.height * ( currentItem + 1 ), finger );
  }
  
  void Update()
  {
    if ( gameptr == nullptr )
    {
      if ( digitalRead( static_cast<uint8_t>( PinButton::Up ) ) )
        MoveUp();
      else if ( digitalRead( static_cast<uint8_t>( PinButton::Down ) ) )
        MoveDown();
      else if ( digitalRead( static_cast<uint8_t>( PinButton::Right ) ) )
        Select();
    }
    else if ( digitalRead( static_cast<uint8_t>( PinButton::RightUp ) ) == false )
    {
      gameptr->UpdateGame();
    }
    else
    {
      delete( gameptr );
      gameptr = nullptr;
    }
  }
  
  void MoveUp()
  {
    if( currentItem > 0 )
      --currentItem;
  }
  
  void MoveDown()
  {
    if( currentItem < ( itemsCount - 1 ) )
      ++currentItem;
  }

  void Select()
  {
    delete( gameptr );
    if ( currentItem == 0 )
      gameptr = new Game15Arduino();
    else if ( currentItem == 1 )
      gameptr = new SnakeArduino();
  }

private:
  static constexpr char* names[] = 
  {
    "1. 15",
    "2. Snake"
  };
  static constexpr uint8_t itemsCount = sizeof(names)/ sizeof(names[0]);
  uint8_t currentItem = 0;
  GamePrototype* gameptr = nullptr;
};

#endif // MENU_H
