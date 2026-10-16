#include <LPC21xx.H>

#define DACR (*((volatile unsigned long *)0xE006C000))
// DAC register address

void delay(unsigned int t)
{
    unsigned int i;

    for(i = 0; i < t; i++);
}

int main(void)
{
    unsigned int value;

    // Configure P0.25 as DAC output (AOUT)
    PINSEL1 |= 0x00080000;

    while(1)
    {
        // Increasing ramp
        for(value = 0; value <= 1023; value++)
        {
            DACR = (value << 6);
            delay(50);
        }

        // Decreasing ramp
        for(value = 1023; value > 0; value--)
        {
            DACR = (value << 6);
            delay(50);
        }
    }
}