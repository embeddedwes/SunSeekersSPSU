#include "solar.h"

unsigned long timer0; //delay_ms routine uses this

void setupDelay()
{
	ET2 = 1; //enable timer 2 interrupt, default priority

	TMR2CN  = 0x00;
	CKCON  &= ~0x60;

	TMR2RLL = 0x17;
	TMR2RLH = 0xfc;
	TMR2L = 0xff;
	TMR2H = 0xff;

	TR2 = 1; //start timer
}

void timer_tick() interrupt 5
{
	timer0--;
	TF2H = 0;
}

void delay_ms(unsigned long milliseconds)
{
	timer0 = milliseconds;
	while(timer0 <= milliseconds) {}
}

void delay_sec(unsigned char seconds)
{
	delay_ms(seconds * 1000);
}