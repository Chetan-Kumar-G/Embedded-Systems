#include <LPC21xx.H>

#define RS  (1<<24)
#define EN  (1<<25)

#define LCD_DATA_MASK 0x00FF0000

void delay(unsigned int t)
{
    unsigned int i, j;

    for(i = 0; i < t; i++)
        for(j = 0; j < 1000; j++);
}

void lcd_cmd(unsigned char cmd)
{
    IOCLR0 = LCD_DATA_MASK;
    IOSET0 = ((unsigned long)cmd << 16);

    IOCLR1 = RS;
    IOSET1 = EN;
    delay(1);
    IOCLR1 = EN;

    delay(2);
}

void lcd_data(unsigned char data)
{
    IOCLR0 = LCD_DATA_MASK;
    IOSET0 = ((unsigned long)data << 16);

    IOSET1 = RS;
    IOSET1 = EN;
    delay(1);
    IOCLR1 = EN;

    delay(2);
}

void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}

void lcd_init(void)
{
    IODIR0 |= LCD_DATA_MASK;
    IODIR1 |= RS | EN;

    delay(20);

    lcd_cmd(0x38);     // 8-bit, 2-line
    lcd_cmd(0x0C);     // Display ON, cursor OFF
    lcd_cmd(0x06);     // Increment cursor
    lcd_cmd(0x01);     // Clear display

    delay(5);
}

void lcd_num(unsigned int num)
{
    lcd_data((num / 10) + '0');
    lcd_data((num % 10) + '0');
}

void rtc_init(void)
{
    CCR = 0x02;        // Reset RTC

    SEC   = 0;
    MIN   = 30;
    HOUR  = 10;

    DOM   = 1;
    DOW   = 4;
    DOY   = 1;
    MONTH = 10;
    YEAR  = 2026;

    CCR = 0x01;        // Enable RTC
}

int main(void)
{
    lcd_init();
    rtc_init();

    while(1)
    {
        lcd_cmd(0x80);
        lcd_string("TIME: ");

        lcd_num(HOUR);
        lcd_data(':');

        lcd_num(MIN);
        lcd_data(':');

        lcd_num(SEC);

        lcd_cmd(0xC0);
        lcd_string("DATE: ");

        lcd_num(DOM);
        lcd_data('/');

        lcd_num(MONTH);
        lcd_data('/');

        lcd_num(YEAR / 100);
        lcd_num(YEAR % 100);

        delay(500);
    }
}