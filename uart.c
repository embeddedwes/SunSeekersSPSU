#include "solar.h"

unsigned char buffer[10], uart_index;

void setupUART0()
{
	memset(buffer, 0, 10); //clear buffer
	uart_index = 0; //init variables

	//enable global interrupts, in case not already done
	EA = 1;

	//enable uart0 interrupts
	ES0 = 1;

	//clock source = timer1 (mode 2) - 9600 baud (9615)
	CKCON |= 1;

	TL1 = 0x64;
	TH1 = 0x64; //100

	//setup timer 1
	TMOD = (1 << 5);

	//start timer 1
	TR1 = 1;

	//SCON0 defaults (could set MCE0 to 1)

	//SBUF0 - write byte to send data

	//start receiving now
	SCON0 |= (1 << 4);
}

void print(unsigned char *message)
{
	int i;

	for(i = 0; i < strlen(message); i++)
	{
		SBUF0 = message[i];
	}
}

void read(unsigned char *message)
{
	strcpy(message, buffer);
}

//must clear interrupt flag inside interrupt based off receive or transmit
//ISR goes here
void uart0() interrupt 4
{
	if(RI0 == 1)
	{
		//read SBUF0 data here and store it or something like that
		buffer[uart_index] = SBUF0;
		uart_index++;
		if(uart_index == 10) { uart_index = 0; } //reset to beginning = circular buffer
		RI0 = 0;
	}
	else if(TI0 == 1)
	{
		//nothing yet
		TI0 = 0;
	}
}
