#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

static uint8_t ScreenWidth = 128;
static uint8_t ScreenHeight = 64;

static U8G2_SH1106_128X64_NONAME_1_HW_I2C Graphics( U8G2_R0, /* reset=*/ U8X8_PIN_NONE );

struct TextHeightWidth
{
  TextHeightWidth(const char* str)
  : height( Graphics.getMaxCharHeight() ),
    width( Graphics.getStrWidth( str ) ) {}

  uint32_t height, width;
};

#endif // GRAPHICS_H
