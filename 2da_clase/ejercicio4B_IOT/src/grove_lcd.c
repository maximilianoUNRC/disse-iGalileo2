/*
  rgb_lcd.cpp
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

#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "grove_lcd.h"
#include "mraa/i2c.h"



void i2c_send_byte(unsigned char dta)
{
    mraa_i2c_write_byte(grove_lcd, dta);
}

void i2c_send_byteS(unsigned char *dta, unsigned char len)
{
    mraa_i2c_write(grove_lcd, dta, len);
}

void grove_lcd_begin(uint8_t cols, uint8_t lines)
{
	uint8_t dotsize = LCD_5x8DOTS;

    grove_lcd = mraa_i2c_init(0);
    grove_rgb = mraa_i2c_init(0);
    mraa_i2c_address(grove_lcd, LCD_ADDRESS);
    mraa_i2c_address(grove_rgb, RGB_ADDRESS);

    if (lines > 1) {
        _displayfunction |= LCD_2LINE;
    }
    _numlines = lines;
    _currline = 0;

    // for some 1 line displays you can select a 10 pixel high font
    if ((dotsize != 0) && (lines == 1)) {
        _displayfunction |= LCD_5x10DOTS;
    }

    // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
    // according to datasheet, we need at least 40ms after power rises above 2.7V
    // before sending commands. Arduino can turn on way before 4.5V so we'll wait 50ms
   usleep(50000);


    // this is according to the hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
    grove_lcd_command(LCD_FUNCTIONSET | _displayfunction);
    usleep(4500);

    // second try
    grove_lcd_command(LCD_FUNCTIONSET | _displayfunction);
    usleep(150);

    // third go
    grove_lcd_command(LCD_FUNCTIONSET | _displayfunction);


    // finally, set # lines, font size, etc.
    grove_lcd_command(LCD_FUNCTIONSET | _displayfunction);

    // turn the display on with no cursor or blinking default
    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    grove_lcd_display();

    // clear it off
    grove_lcd_clear();

    // Initialize to default text direction (for romance languages)
    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    // set the entry mode
    grove_lcd_command(LCD_ENTRYMODESET | _displaymode);


    // backlight init
    grove_lcd_setReg(0, 0);
    grove_lcd_setReg(1, 0);
    grove_lcd_setReg(0x08, 0xAA);     // all led control by pwm

    grove_lcd_setColorWhite();

}

/********** high level commands, for the user! */
void grove_lcd_clear()
{
	grove_lcd_command(LCD_CLEARDISPLAY);        // clear display, set cursor position to zero
    usleep(2000);          // this command takes a long time!
}

void grove_lcd_home()
{
	grove_lcd_command(LCD_RETURNHOME);        // set cursor position to zero
    usleep(2000);        // this command takes a long time!
}

void grove_lcd_setCursor(uint8_t col, uint8_t row)
{

    col = (row == 0 ? col|0x80 : col|0xc0);
    unsigned char dta[2] = {0x80, col};

    i2c_send_byteS(dta, 2);

}

// Turn the display on/off (quickly)
void grove_lcd_noDisplay()
{
    _displaycontrol &= ~LCD_DISPLAYON;
    grove_lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}


void grove_lcd_display() {
    _displaycontrol |= LCD_DISPLAYON;
    grove_lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void grove_lcd_noCursor()
{
    _displaycontrol &= ~LCD_CURSORON;
    grove_lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void grove_lcd_cursor() {
    _displaycontrol |= LCD_CURSORON;
    grove_lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void grove_lcd_noBlink()
{
    _displaycontrol &= ~LCD_BLINKON;
    grove_lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void grove_lcd_blink()
{
    _displaycontrol |= LCD_BLINKON;
    grove_lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void grove_lcd_scrollDisplayLeft(void)
{
	grove_lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void grove_lcd_scrollDisplayRight(void)
{
	grove_lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void grove_lcd_leftToRight(void)
{
    _displaymode |= LCD_ENTRYLEFT;
    grove_lcd_command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void grove_lcd_rightToLeft(void)
{
    _displaymode &= ~LCD_ENTRYLEFT;
    grove_lcd_command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void grove_lcd_autoscroll(void)
{
    _displaymode |= LCD_ENTRYSHIFTINCREMENT;
    grove_lcd_command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void grove_lcd_noAutoscroll(void)
{
    _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
    grove_lcd_command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void grove_lcd_createChar(uint8_t location, uint8_t charmap[])
{

    location &= 0x7; // we only have 8 locations 0-7
    grove_lcd_command(LCD_SETCGRAMADDR | (location << 3));


    unsigned char dta[9];
    dta[0] = 0x40;
    int i;
    for(i=0; i<8; i++)
    {
        dta[i+1] = charmap[i];
    }
    i2c_send_byteS(dta, 9);
}

/*********** mid level commands, for sending data/cmds */

// send command
inline void grove_lcd_command(uint8_t value)
{
    unsigned char dta[2] = {0x80, value};
    i2c_send_byteS(dta, 2);
}

// send data
size_t grove_lcd_write(char * str)
{
	int i;
	for(i=0; i < strlen((const char*)str); i++) {
		unsigned char dta[2] = {0x40, str[i]};
		i2c_send_byteS(dta, 2);
	}
    return 1; // assume success
}

void grove_lcd_setReg(unsigned char addr, unsigned char dta)
{
	unsigned char rx_tx_buf[2];
    rx_tx_buf[0] = addr;
    rx_tx_buf[1] = dta;
    mraa_i2c_write(grove_rgb, rx_tx_buf, 2);
}

void grove_lcd_setRGB(unsigned char r, unsigned char g, unsigned char b)
{
	grove_lcd_setReg(REG_RED, r);
	grove_lcd_setReg(REG_GREEN, g);
	grove_lcd_setReg(REG_BLUE, b);
}

const unsigned char color_define[4][3] =
{
    {255, 255, 255},            // 0 = white
    {255, 0, 0},                // 1 = red
    {0, 255, 0},                // 2 = green
    {0, 0, 255},                // 3 = blue
};

void grove_lcd_setColor(unsigned char color)
{
    if(color > 3)return ;
    grove_lcd_setRGB(color_define[color][0], color_define[color][1], color_define[color][2]);
}

void grove_lcd_setPWM(unsigned char color, unsigned char pwm){grove_lcd_setReg(color, pwm);}      // set pwm

void grove_lcd_setColorAll(){grove_lcd_setRGB(0, 0, 0);}
void grove_lcd_setColorWhite(){grove_lcd_setRGB(255, 255, 255);}
