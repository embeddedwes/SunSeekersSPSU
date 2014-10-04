/*Compiler headers*/
#include <c8051f340.h>

/*C headers*/
#include <string.h>
#include <stdio.h>

/*Additional file headers if needed*/


/*Define statements*/

#define SYSCLK 12000000
#define BAUDRATE 9600

#define CW 0
#define CCW 1

#define STEPS_PER_REV 4076

/*Macros if needed*/


/*Function definitions*/
void disableWatchdog(void);
void setupClock(void);
void enableInterrupts(void);

void setupGPIO(void);

void step(unsigned char direction);
void rotateDegrees(unsigned char direction, unsigned int degrees);
void rotateRevolutions(unsigned char direction, unsigned char revolutions);

void setupDelay(void);
void delay_ms(unsigned long milliseconds);
void delay_sec(unsigned char seconds);
void timer_tick(void);

void setupUART0(void);

void setupAnalog(void);
int analogRead(unsigned char pin);
int analogSample(unsigned char pin, unsigned char samples, unsigned char delay);