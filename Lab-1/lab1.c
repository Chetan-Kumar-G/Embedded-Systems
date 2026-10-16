//CH.SC.U4CSE24109
#include <LPC21xx.h>

void delay(void);

int main()
{
    IO0DIR |= (1 << 0);      // Set P0.0 as Output

    while(1)
    {
        IO0SET = (1 << 0);   // LED ON
        delay();

        IO0CLR = (1 << 0);   // LED OFF
        delay();
    }
}

void delay(void)
{
    unsigned int i;

    for(i = 0; i < 200000; i++);
}
