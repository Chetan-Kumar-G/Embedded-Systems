#include <LPC21xx.H>

void delay(unsigned int t)
{
	unsigned int i;
	for(i=0; i<t; i++);
}

void UART0_Init(void)
{
	PINSEL0 |= 0x00000005;   // P0.0 = TXD0, P0.1 = RXD0

	U0LCR = 0x83;              // 8 bits, 1 stop, no parity, DLAB=1
	U0DLL = 16;                // Baud rate divisor (9600 baud @ 2.5MHz PCLK)
	U0DLM = 0;
	U0LCR = 0x03;              // DLAB=0, 8-bit mode
}

void UART0_SendChar(unsigned char ch)
{
	U0THR = ch;
	while(!(U0LSR & 0x20));   // Wait until THR empty
}

void UART0_SendString(char *str)
{
	while(*str)
	{
		UART0_SendChar(*str);
		str++;
	}
}

int main(void)
{
	UART0_Init();

	while(1)
	{
		UART0_SendString("Hello, im chetan\r\n");
		delay(1000000);
	}
}