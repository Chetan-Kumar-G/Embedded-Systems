#include <LPC21xx.H>

#define LED 0x00000001

int main(void)
{
	PINSEL0 = 0x00000000;
	IO0DIR = LED;
	IO0CLR = LED;           // LED starts OFF

	PINSEL1 |= 0x00000001;  // P0.16 as EINT0

	EXTMODE = 0x01;          // Edge-triggered
	EXTPOLAR = 0x01;         // Rising edge
	EXTINT = 0x01;           // Clear any stale flag

	while(1)
	{
		if (EXTINT & 0x01)        // Button press detected
		{
			IO0PIN ^= LED;          // Toggle LED state
			EXTINT = 0x01;           // Clear flag

			while(EXTINT & 0x01);   // (safety) wait if flag re-sets immediately
		}
	}
}