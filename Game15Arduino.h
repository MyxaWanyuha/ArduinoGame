#ifndef GAME15_ARDUINO_H
#define GAME15_ARDUINO_H

#include "Graphics.h"
#include "Game15.h"
#include "GamePrototype.h"

class Game15Arduino : protected Game, public GamePrototype
{
	virtual void Render() override
	{
    if( Mode == GameMode::Ready )
    {
      Graphics.setFont(u8g2_font_ncenB10_tr);
      Graphics.drawStr(6, 24, "MyxaWanyuha");
      Graphics.drawStr(20, 40, "15");

      Graphics.setFont(u8g2_font_ncenB08_tr);
      int fw = Graphics.getStrWidth("Press any key");
      int fh = Graphics.getMaxCharHeight();
      if( intro_state )
        Graphics.drawStr(10, 55, "Press any key");
      else
        Graphics.drawBox(10,55-fh,fw,fh); // remove text
    }
    else if( Mode == GameMode::Reset )
    {
      Graphics.setFont(u8g2_font_ncenB10_tr);
      Graphics.drawStr(8, 24, "Gameover");
    }
    else if( Mode == GameMode::Game )
    {
      Graphics.setFont(u8g2_font_ncenB14_tr);
      for(int x = 0; x < width; ++x)
        for(int y = 0; y < width; ++y)
        {
          char buf[5];
          char* num = itoa(GetCellValue(x, y), buf, 10);
          String s(GetCellValue(x, y));
          int fw = Graphics.getStrWidth(num);
          int fh = Graphics.getMaxCharHeight();
          if(GetCellValue(x, y) != width * width)
            Graphics.drawStr(fw * (x + 1) * 2, fh * (y + 1), s.c_str());
        }
    }
  }

	virtual void Update() override
	{
    if(ButtonUp)
      MoveLeft();
    else if (ButtonDown)
      MoveRight();
    else if (ButtonLeft)
      MoveUp();
    else if (ButtonRight)
      MoveDown();
	}

  virtual void ResetGame() override
  {
    MixMap();
  }
};

#endif // GAME15_ARDUINO_H
