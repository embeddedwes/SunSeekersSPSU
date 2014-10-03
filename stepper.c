#include "solar.h"

//moving through the pinState array indices in a positive direction causes counter clockwise direction
//note that we are half stepping through the values here, which gives finer resolution of stepper motor
unsigned char pinState[8] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09};
unsigned char index = 0;

void step(unsigned char direction)
{
	//incrementing or decrementing index variable based off of parameter
	if(direction == CW)
	{
		index--;
	}
	else if(direction == CCW)
	{
		index++;
	}
	
	//checking for any end of array conditions and forcing a wrap around to start or end of array (if needed)
	if (index == 8)
	{
		index = 0;
	}
	else if(index == 255)
	{
		index = 7;
	}
	
	//set port 4 based off of array and index - physically changes logic levels of port 4
	//not that the upper four bits of port 4 are always 0 (intentionally because of array) and so cooresponding pins (see datasheet pinout diagram) will always be logic low
	//only the first four pins belonging to port 4 are used to control the stepper motor (P4.0 through P4.3)
	//P4.0 = pin 22
	//P4.1 = pin 21
	//P4.2 = pin 20
	//P4.3 = pin 19
	//P4.4 through P4.7 unused (pins 15-18 inclusive)
	P4 = pinState[index];
}

//the largest degree value that can be accepted is 65,535 (unsigned int = 16 bits)
void rotateDegrees(unsigned char direction, unsigned int degrees)
{
	unsigned long i, steps; //must be of type unsigned long to be able to hold large numbers that result from multiplication by 4076 below when using high degree counts

	steps = (degrees / 360.0) * STEPS_PER_REV; //4076 (half) steps per full revolution
	//you must divide by 360.0 not 360, because without the '.0' the device will do integer math (not float) and round down to 0 and your motor will never spin at all

	for(i = 0; i < steps; i++)
	{
		step(direction);

		//max speed occurs with 7 millisecond delay
		delay_ms(10);
	}
}

//simple extension function for ease of use; largest # of revolutions = 182 (any higher and the rotateDegrees function parameter will overflow)
void rotateRevolutions(unsigned char direction, unsigned char revolutions)
{
	rotateDegrees(direction, revolutions * 360);
}
	
