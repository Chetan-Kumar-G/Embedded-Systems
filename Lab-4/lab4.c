#include <LPC21xx.h>

#define LCD_DATA 0x000000FF      // P0.0 to P0.7
#define RS (1<<16)
#define EN (1<<17)

void delay(unsigned int t)
{
    unsigned int i,j;
    for(i=0;i<t;i++)
        for(j=0;j<600;j++);
}

void lcd_cmd(unsigned char cmd)
{
    IOCLR0 = LCD_DATA;
    IOSET0 = cmd;

    IOCLR0 = RS;       // Command mode

    IOSET0 = EN;
    delay(2);
    IOCLR0 = EN;

    delay(5);
}

void lcd_data(unsigned char data)
{
    IOCLR0 = LCD_DATA;
    IOSET0 = data;

    IOSET0 = RS;       // Data mode

    IOSET0 = EN;
    delay(2);
    IOCLR0 = EN;

    delay(5);
}

void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}

void lcd_init()
{
    delay(20);

    lcd_cmd(0x38);   // 8-bit, 2-line
    lcd_cmd(0x0C);   // Display ON
    lcd_cmd(0x06);   // Cursor increment
    lcd_cmd(0x01);   // Clear display
}

int main()
{
    IODIR0 = LCD_DATA | RS | EN;

    lcd_init();

    lcd_string("HELLO");

    lcd_cmd(0xC0);      // Second line

    lcd_string("LPC2138 LCD");

    while(1);
}