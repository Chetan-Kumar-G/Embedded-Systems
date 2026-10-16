#include <LPC21xx.H>

#define LED 0x00000001   // P0.0

int main(void)
{
	PINSEL0 = 0x00000000;
	IO0DIR = LED;

	T0TCR = 0x02;        // Reset Timer0
	T0PR  = 0;           // Prescaler = 0
	T0MR0 = 50000;       // Match value (controls toggle speed)
	T0MCR = 0x03;        // Interrupt flag + reset TC on MR0 match
	T0TCR = 0x01;        // Enable Timer0

	while(1)
	{
		while(!(T0IR & 0x01));   
		T0IR = 0x01;              
		IO0PIN ^= LED;            
	}
}