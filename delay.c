#include "solar.h"

unsigned long timer0; //delay routine uses this

void setup_delay()
{
	EA = 1; //globally enable interrupts
	ET2 = 1; //enable timer 2 interrupt
	//leave timer 2 interrupt as default priority for now

	TMR2CN  = 0x00; // Stop Timer2; Clear TF2;
                    // Use SYSCLK/12 as timebase
	CKCON  &= ~0x60; // Timer2 clocked based on T2XCLK;

	TMR2RL  = 0xffff-125; // Init reload values
	TMR2    = 0xffff; // Set to reload immediately

	  OSCICN = 0x80;                    // Configure internal oscillator for
                                       // its lowest frequency

	//enable timer 2
	TR2 = 1;
}

//interrupt ISR
//note that we do not have to clear timer interrupt flag like other interrupts because hardware clears it for us
//timer0 interrupt # is 1
void timer() interrupt 5
{
	timer0--;
}

//delay for x milliseconds
void delay_ms(unsigned long milliseconds)
{
	timer0 = milliseconds;
	while(timer0 <= milliseconds) {} //wait and do nothing while time goes by, this while loop will exit and this function will return when x milliseconds have expired
}

//delay for x seconds, extension function for delay_ms()
void delay_sec(unsigned char seconds)
{
	delay_ms(seconds * 1000);
}