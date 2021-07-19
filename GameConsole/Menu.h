#ifndef MENU_H
#define MENU_H
#include <Arduino.h>
#include "GamePrototype.h"
#include "MenuGames.h"

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

    Graphics.firstPage();
    do
    {
      Graphics.setFont( u8g2_font_ncenB10_tr ); // 4 lines on screen
      const uint8_t maxLinesCountOnScreen = 4;
      const TextHeightWidth nameHW( menuGames[0].gameName );
      for( uint8_t i = currentItem; i < gamesCount && i < ( maxLinesCountOnScreen + currentItem ) ; ++i )
      {
        Graphics.drawStr( 10, 
        nameHW.height * ( ( ( i - currentItem ) % maxLinesCountOnScreen ) + 1 ),
        menuGames[i].gameName );
      }
      const char* finger = "> ";
      Graphics.drawStr( 0, nameHW.height, finger );
    } 
    while( Graphics.nextPage() );
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
    {
      soundManager.Beep();
      --currentItem;
      delay(150);
    }
  }
  
  void MoveDown()
  {
    if( currentItem < ( gamesCount - 1 ) )
    {
      soundManager.Beep();
      ++currentItem;
      delay(150);
    }
  }

  void Select()
  {
    soundManager.Beep();
    delete( gameptr );
    gameptr = menuGames[currentItem].GetNewGame();
  }

private:
  uint8_t currentItem = 0;
  GamePrototype* gameptr = nullptr;
  static const uint8_t gamesCount;
};

static const uint8_t Menu::gamesCount = sizeof(menuGames) / sizeof(menuGames[0]);

#endif // MENU_H
