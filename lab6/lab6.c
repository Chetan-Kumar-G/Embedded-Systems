#include <LPC21xx.H>

/* LCD control pins */
#define RS  (1 << 0)       // P0.0
#define RW  (1 << 1)       // P0.1
#define EN  (1 << 2)       // P0.2

/* ADC registers */
#define AD0CR  (*((volatile unsigned long *)0xE0034000))
#define AD0GDR (*((volatile unsigned long *)0xE0034004))

void delay(unsigned int t)
{
    unsigned int i;
    for(i = 0; i < t; i++);
}

/* Send command to LCD */
void lcd_cmd(unsigned char cmd)
{
    IO1PIN = (IO1PIN & 0x00FFFFFF) | ((unsigned long)cmd << 24);

    IO0CLR = RS;
    IO0CLR = RW;
    IO0SET = EN;

    delay(1000);

    IO0CLR = EN;

    delay(5000);
}

/* Send data to LCD */
void lcd_data(unsigned char data)
{
    IO1PIN = (IO1PIN & 0x00FFFFFF) | ((unsigned long)data << 24);

    IO0SET = RS;
    IO0CLR = RW;
    IO0SET = EN;

    delay(1000);

    IO0CLR = EN;

    delay(5000);
}

/* LCD initialization */
void lcd_init(void)
{
    lcd_cmd(0x38);      // 8-bit, 2-line, 5x7
    lcd_cmd(0x0C);      // Display ON, cursor OFF
    lcd_cmd(0x01);      // Clear display
    lcd_cmd(0x06);      // Increment cursor
    delay(10000);
}

/* Display string */
void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str);
        str++;
    }
}

/* Display integer */
void lcd_number(unsigned int num)
{
    char buffer[6];
    int i = 0;

    if(num == 0)
    {
        lcd_data('0');
        return;
    }

    while(num > 0)
    {
        buffer[i] = (num % 10) + '0';
        num = num / 10;
        i++;
    }

    while(i > 0)
    {
        i--;
        lcd_data(buffer[i]);
    }
}

/* ADC read function */
unsigned int ADC_Read(void)
{
    unsigned int value;

    /* 
       Select AD0.0
       CLKDIV = 4
       ADC enabled
    */
    AD0CR = (1 << 0) | (4 << 8) | (1 << 21);

    /* Start conversion */
    AD0CR |= (1 << 24);

    /* Wait until conversion completes */
    while((AD0GDR & (1UL << 31)) == 0);

    /* Extract 10-bit result */
    value = (AD0GDR >> 6) & 0x3FF;

    /* Stop conversion */
    AD0CR &= ~(7 << 24);

    return value;
}

int main(void)
{
    unsigned int adc_value;

    /* P0.27 = AD0.0
       Bits 22:23 of PINSEL1 = 01
    */
    PINSEL1 &= ~(3UL << 22);
    PINSEL1 |=  (1UL << 22);

    /* LCD control pins P0.0, P0.1, P0.2 as output */
    IO0DIR |= RS | RW | EN;

    /* LCD data pins P1.24 - P1.31 as output */
    IO1DIR |= 0xFF000000;

    /* Initialize LCD */
    lcd_init();

    /* Display heading */
    lcd_cmd(0x80);
    lcd_string("ADC VALUE:");

    while(1)
    {
        /* Read ADC */
        adc_value = ADC_Read();

        /* Move to second line */
        lcd_cmd(0xC0);

        /* Display ADC value */
        lcd_number(adc_value);

        /* Clear remaining characters */
        lcd_string("     ");

        delay(50000);
    }
}