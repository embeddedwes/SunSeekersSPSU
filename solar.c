#include "solar.h" //include all other header files in here

//all documentation references found below can be seen at
//http://www.silabs.com/Support%20Documents/TechnicalDocs/c8051f34x.pdf

int main()
{
	//don't remove for now, this disable WDT (watchdog timer) and prevents microcontroller from continually restarting
	disableWatchdog();

	setup_delay();

	setupUART0();
	
	//setup open-drain vs push-pull and setup input/output and a few other things too
	setupGPIO();

	/*loop code here to run over and over again*/
	while(1) {
		//rotateDegrees(CW, 180); //rotate half a revolution CW
		//rotateRevolutions(CCW, 2); //rotate 2 revolutions CCW
		print("test\n");
		delay_sec(100);
	}
	
	//last line of code the micro controller can run, should never get here since once this code runs the micro controller wont do anything useful again until it is restarted
	//should stay in the while loop forever
	return 0;
}