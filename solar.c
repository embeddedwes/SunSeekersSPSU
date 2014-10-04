#include "solar.h"

//all documentation references found below can be seen at
//http://www.silabs.com/Support%20Documents/TechnicalDocs/c8051f34x.pdf

int main()
{
	int value;
	unsigned char message[20];

	disableWatchdog();
	setupClock();
	enableInterrupts();

	setupDelay();
	setupGPIO();
	setupUART0();
	setupAnalog();

	while(1) {
		rotateDegrees(CW, 180); //rotate half a revolution CW
		rotateRevolutions(CCW, 1); //rotate 2 revolutions CCW
		printf("once around the loop\n");
		value = analogSample(29, 5, 10);
		sprintf(message, "value: %u\n", value);
		printf(message);
		delay_sec(1);
	}
	
	return 0;
}