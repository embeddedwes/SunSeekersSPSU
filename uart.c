#include "solar.h"

void setupUART0()
{
	SCON0 = 0x10; //8 bit mode, variable baud rate, STOP bit logic level ignored, RX enabled, clear UART interrupts

	if (SYSCLK/BAUDRATE/2/256 < 1) {
		TH1 = -(SYSCLK/BAUDRATE/2);

		CKCON &= ~0x0B;
		CKCON |=  0x08;
	} else if (SYSCLK/BAUDRATE/2/256 < 4) {
		TH1 = -(SYSCLK/BAUDRATE/2/4);

		CKCON &= ~0x0B;               
		CKCON |=  0x01;
	} else if (SYSCLK/BAUDRATE/2/256 < 12) {
		TH1 = -(SYSCLK/BAUDRATE/2/12);

		CKCON &= ~0x0B;
	} else {
		TH1 = -(SYSCLK/BAUDRATE/2/48);

		CKCON &= ~0x0B;
		CKCON |=  0x02;
	}

	TL1 = TH1; //init timer1

	TMOD &= ~0xf0; //timer 1 = 8 bit auto reload mode
	TMOD |=  0x20;
	                
	TR1 = 1; //start timer1
	TI0 = 1; //TX0 ready
}