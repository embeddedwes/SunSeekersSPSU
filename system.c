#include "solar.h"

void disableWatchdog()
{
	PCA0MD &= ~0x40; //disables watchdog timer
}

void setupClock()
{
	OSCICN |= 0x03; //max internal oscillator frequency
	RSTSRC  = 0x04; //missing clock detector
}

void enableInterrupts()
{
	EA = 1; //enable global interrupts bit
}