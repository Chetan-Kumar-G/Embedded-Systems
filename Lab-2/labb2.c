//CH.SC.U4CSE24109
#include <LPC21xx.h>
#define SW1  (1<<0)      // Switch at P0.0
#define SW2  (1<<1)      // Switch at P0.1
#define LED1 (1<<16)     // LED1 at P0.16
#define LED2 (1<<17)     // LED2 at P0.17

int main(void)
{
    // Configure LEDs as output
    IODIR0 |= (LED1 | LED2);

    // Configure switches as input
    IODIR0 &= ~(SW1 | SW2);

    while(1)
    {
        // Switch 1
        if(IOPIN0 & SW1)
            IOSET0 = LED1;
        else
            IOCLR0 = LED1;

        // Switch 2
        if(IOPIN0 & SW2)
            IOSET0 = LED2;
        else
            IOCLR0 = LED2;
    }
}