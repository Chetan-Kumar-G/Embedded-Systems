#include <LPC21xx.h>

// Delay Function
void delay(unsigned int t)
{
    unsigned int i, j;
    for(i = 0; i < t; i++)
        for(j = 0; j < 6000; j++);
}

// Common Cathode Seven Segment Codes
unsigned char digit[10] =
{
    0x3F,   //0
    0x06,   //1
    0x5B,   //2
    0x4F,   //3
    0x66,   //4
    0x6D,   //5
    0x7D,   //6
    0x07,   //7
    0x7F,   //8
    0x6F    //9
};

int main()
{
    int i;

    IO0DIR = 0xFF;      // P0.0 - P0.7 as output

    while(1)
    {
        for(i = 0; i < 10; i++)
        {
            IO0CLR = 0xFF;          // Clear previous value
            IO0SET = digit[i];      // Display current digit
            delay(10);
        }
    }
}