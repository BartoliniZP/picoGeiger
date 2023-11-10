#include "LiquidCrystal_I2C.h"

void LiquidCrystal_I2C::write(char value)
{
    send(value, Rs);
}

void LiquidCrystal_I2C::init(uint8_t dotsize)
{
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
    if (_rows > 1)
    {
        _displayfunction |= LCD_2LINE;
    }

    if ((dotsize != 0) && (_rows == 1))
    {
        _displayfunction |= LCD_5x10DOTS;
    }

    sleep_ms(50);

    expanderWrite(_backlightval);
    sleep_ms(1000);

    write4bits(0x03 << 4);
    sleep_us(4500);

    write4bits(0x03 << 4);
    sleep_us(4500);

    write4bits(0x03 << 4);
    sleep_us(150);

    write4bits(0x02 << 4);

    command(LCD_FUNCTIONSET | _displayfunction);

    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    display();

    clear();

    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    command(LCD_ENTRYMODESET | _displaymode);

    home();
}

void LiquidCrystal_I2C::clear()
{
    command(LCD_CLEARDISPLAY); // clear display, set cursor position to zero
    sleep_ms(2000);            // this command takes a long time!
}

void LiquidCrystal_I2C::home()
{
    command(LCD_RETURNHOME); // set cursor position to zero
    sleep_ms(2000);          // this command takes a long time!
}

void LiquidCrystal_I2C::setCursor(uint8_t col, uint8_t row)
{
    int row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    if (row > _numlines)
    {
        row = _numlines - 1; // we count rows starting w/0
    }
    command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void LiquidCrystal_I2C::noDisplay()
{
    _displaycontrol &= ~LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C::display()
{
    _displaycontrol |= LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void LiquidCrystal_I2C::noCursor()
{
    _displaycontrol &= ~LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C::cursor()
{
    _displaycontrol |= LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C::noBlink()
{
    _displaycontrol &= ~LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C::blink()
{
    _displaycontrol |= LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void LiquidCrystal_I2C::scrollDisplayLeft()
{
    command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void LiquidCrystal_I2C::scrollDisplayRight()
{
    command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void LiquidCrystal_I2C::noBacklight(void)
{
    _backlightval = LCD_NOBACKLIGHT;
    expanderWrite(0);
}

void LiquidCrystal_I2C::backlight(void)
{
    _backlightval = LCD_BACKLIGHT;
    expanderWrite(0);
}

// This is for text that flows Left to Right
void LiquidCrystal_I2C::leftToRight()
{
    _displaymode |= LCD_ENTRYLEFT;
    command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void LiquidCrystal_I2C::rightToLeft()
{
    _displaymode &= ~LCD_ENTRYLEFT;
    command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void LiquidCrystal_I2C::autoscroll()
{
    _displaymode |= LCD_ENTRYSHIFTINCREMENT;
    command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void LiquidCrystal_I2C::noAutoscroll()
{
    _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
    command(LCD_ENTRYMODESET | _displaymode);
}

void LiquidCrystal_I2C::command(uint8_t value)
{
    send(value, 0);
}

void LiquidCrystal_I2C::write4bits(uint8_t value)
{
    expanderWrite(value);
    pulseEnable(value);
}

void LiquidCrystal_I2C::expanderWrite(uint8_t val)
{
    i2c_write_blocking(i2c_default, _Addr, &val, 1, false);
}

void LiquidCrystal_I2C::pulseEnable(uint8_t val)
{
    expanderWrite(val | En);
    sleep_us(1);
    expanderWrite(val & ~En);
    sleep_us(50);
}

void LiquidCrystal_I2C::send(uint8_t val, int mode)
{
    uint8_t high = mode | (val & 0xF0) | _backlightval;
    uint8_t low = mode | ((val << 4) & 0xF0) | _backlightval;

    expanderWrite(high);
    pulseEnable(high);
    expanderWrite(low);
    pulseEnable(low);
}

void LiquidCrystal_I2C::printStr(const char *str)
{
    while (*str)
        write(*str++);
}

LiquidCrystal_I2C::LiquidCrystal_I2C(uint8_t lcd_cols, uint8_t lcd_rows, uint8_t dotsize, uint8_t lcd_Addr) : _cols(lcd_cols), _rows(lcd_rows), _Addr(lcd_Addr), _backlightval(LCD_NOBACKLIGHT)
{
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    this->init(dotsize);
}

bool LiquidCrystal_I2C::getBacklightValue()
{
    return (_backlightval == LCD_BACKLIGHT);
}

uint LiquidCrystal_I2C::getColumns()
{
    return _cols;
}

uint LiquidCrystal_I2C::getRows()
{
    return _rows;
}