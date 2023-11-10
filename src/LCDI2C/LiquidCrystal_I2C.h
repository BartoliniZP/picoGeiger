#ifndef LiquidCrystal_I2C_h
#define LiquidCrystal_I2C_h

#include <stdio.h>
#include <string>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
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

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0b00000100 // Enable bit
#define Rw 0b00000010 // Read/Write bit
#define Rs 0b00000001 // Register select bit

#define DEF_ADDR 0x27

class LiquidCrystal_I2C
{
public:
    LiquidCrystal_I2C(uint8_t lcd_cols, uint8_t lcd_rows, uint8_t dotsize = LCD_5x8DOTS, uint8_t lcd_Addr = DEF_ADDR);
    void write(char);
    void expanderWrite(uint8_t val);
    void send(uint8_t val, int mode);
    void pulseEnable(uint8_t val);
    void init(uint8_t);
    void write4bits(uint8_t value);
    void command(uint8_t value);
    void display();
    void noDisplay();
    void clear();
    void home();
    void setCursor(uint8_t col, uint8_t row);
    void noCursor();
    void cursor();
    void noBlink();
    void blink();
    void autoscroll();
    void noAutoscroll();
    void rightToLeft();
    void leftToRight();
    void scrollDisplayLeft();
    void scrollDisplayRight();
    void noBacklight();
    void backlight();
    void printStr(const char *str);
    bool getBacklightValue();

    uint getRows();
    uint getColumns();

private:
    uint8_t _Addr;
    uint8_t _displayfunction;
    uint8_t _displaycontrol;
    uint8_t _displaymode;
    uint8_t _numlines;
    uint8_t _cols;
    uint8_t _rows;
    uint8_t _backlightval;
};

#endif