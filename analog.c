#include "solar.h"

void setupAnalog(void)
{
   P3MDIN &= ~0x02;

   REF0CN = 0x03;
   REF0CN |= (1 << 3);
   AMX0P = 7; //3.1
   AMX0N = 0x1F; //ground - single sided

   ADC0CF = ((SYSCLK/3000000)-1)<<3; // set SAR clock to 3MHz
   AD0EN = 1; //enable adc0
}

int analogRead(unsigned char pin)
{
	ADC0CN &= ~(1 << 5);
	AD0BUSY = 1;
	while(ADC0CN & (1 << 5) == 0) {}
	return ((ADC0H & 0x3) << 8) + ADC0L;
}

int analogSample(unsigned char pin, unsigned char samples, unsigned char delay)
{
	unsigned char i;
	int value = 0;

	for(i = 0; i < samples; i++)
	{
		value += analogRead(pin);
		delay_ms(delay);
	}

	return value / samples;
}