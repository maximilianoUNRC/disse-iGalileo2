/*
  rgb_lcd.h
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.
  Author:Loovee
  2013-9-18
  add rgb backlight function @ 2013-10-15

  The MIT License (MIT)
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.1  USA
*/


#ifndef __RGB_LCD_H__
#define __RGB_LCD_H__

#include <inttypes.h>
#include <stdio.h>
#include <stddef.h>
#include "mraa/i2c.h"

mraa_i2c_context grove_lcd;
mraa_i2c_context grove_rgb;


// Device I2C Address
#define LCD_ADDRESS     (0x7c>>1)
#define RGB_ADDRESS     (0xc4>>1)


// color define
#define WHITE           0
#define RED             1
#define GREEN           2
#define BLUE            3

#define REG_RED         0x04        // pwm2
#define REG_GREEN       0x03        // pwm1
#define REG_BLUE        0x02        // pwm0

#define REG_MODE1       0x00
#define REG_MODE2       0x01
#define REG_OUTPUT      0x08

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

void grove_lcd_begin(uint8_t cols, uint8_t rows);

void grove_lcd_clear();
void grove_lcd_home();

void grove_lcd_noDisplay();
void grove_lcd_display();
void grove_lcd_noBlink();
void grove_lcd_blink();
void grove_lcd_noCursor();
void grove_lcd_cursor();
void grove_lcd_scrollDisplayLeft();
void grove_lcd_scrollDisplayRight();
void grove_lcd_leftToRight();
void grove_lcd_rightToLeft();
void grove_lcd_autoscroll();
void grove_lcd_noAutoscroll();

void grove_lcd_createChar(uint8_t location, uint8_t charmap[]);
void grove_lcd_setCursor(uint8_t col, uint8_t row);

void grove_lcd_command(uint8_t value);

size_t grove_lcd_write(char * str);

// color control
void grove_lcd_setRGB(unsigned char r, unsigned char g, unsigned char b);  // set rgb
void grove_lcd_setPWM(unsigned char color, unsigned char pwm);  // set pwm
void grove_lcd_setColor(unsigned char color);
void grove_lcd_setColorAll();
void grove_lcd_setColorWhite();
void grove_lcd_setReg(unsigned char addr, unsigned char dta);

uint8_t _displayfunction;
uint8_t _displaycontrol;
uint8_t _displaymode;
uint8_t _initialized;
uint8_t _numlines,_currline;

#endif
