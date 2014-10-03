#include "solar.h"

void Setup_Analog (void)
{
   OSCICN = 0x83;                      // configure internal oscillator for
                                       // 12MHz / 1

   P3MDIN &= ~0x02;                    // set P3.1 as an analog input

   REF0CN = 0x03;                      // Enable on-chip VREF and buffer
   REF0CN |= (1 << 3);
   AMX0P = 7;                       // ADC0 positive input = P1.1
   AMX0N = 0x1F;                       // ADC0 negative input = GND
                                       // i.e., single ended mode

   ADC0CF = ((SYSCLK/3000000)-1)<<3;   // set SAR clock to 3MHz

   EIE1 |= 0x08;                       // enable ADC0 conversion complete int.

   AD0EN = 1;                          // enable ADC0

   EA = 1;							   // Enable Global Interrupts.
}

int analogRead(unsigned char pin)
{
	AD0INT = 0;
	AD0BUSY = 1;
	while(ADOINT == 0) {}
	return (ADC0H & 0x3) << 8 + ADC0L;
}

int analogSample(unsigned char pin, unsigned char samples, unsigned char delay)
{
	unsigned char i;
	int value = 0;

	for(i = 0; i < samples; i++)
	{
		value += analogRead(pin);
		//delay_ms(delay);
	}

	return value / samples;
}