#include "solar.h"

void disableWatchdog()
{
	//disables watchdog timer, which unless 'petted' will continually restart micro controller
	PCA0MD &= ~0x40;
}

void setupGPIO()
{
	//Note this function will have to change as we keep adding/removing/changing peripheral devices and communictiaons protocols
	//for now it is setup simply to set port 4 into push/pull mode and to enable the crossbar
	//see page 147 of datasheet section 15.2 for more info and registers etc.

	//step 1 set input mode for any/all pins
	//we don't want analog input mode as this disable digital functions, but since reset value for P4MDIN (page 150) is 0xFF no need to set again
	//P4MDIN = 0xFF;

	//step 2 set output mode
	P4MDOUT = 0xFF; //set push-pull for port 4 not open-drain (all ports default to open-drain)

	//step 3 select pins to skip in crossbar
	//certain pins in the first few ports are dedicated to specific functions such as UART so those can be skipped here if desired, for now we will leave it alone (page 145)

	//step 4 assign port pins to desired peripherals
	//we don't want any peripherals at the moment, just general purpose I/O so don't set any special cases, but here you would enable UART etc.

	//step 5 enable crossbar (crossbar is required to be enabled for ports 0-3 for any digital write functionality at all - page 147)
	//we are using port 4 so technically we don't have to enable this, but we are enabling it anyway since we will eventually be using UART and other functions that require crossbar to be enabled
	XBR1 = 0x40; //set XBARE bit in XBR1 register to 1 (page 149)
}