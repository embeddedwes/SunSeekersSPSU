#include <c8051f340.h> //system header

/*C headers*/
#include  <string.h>

/*Additional file headers if needed*

/*Define statements*/

#define OSCILLATOR 12000000
#define SYSCLK = OSCILLATOR / 12;

#define CW 0
#define CCW 1

#define STEPS_PER_REV 4076

/*Macros*/

/*Function definitions*/
void disableWatchdog(void);
void setupGPIO(void);

void step(unsigned char direction);
void rotateDegrees(unsigned char direction, unsigned int degrees);
void rotateRevolutions(unsigned char direction, unsigned char revolutions);

void setup_delay(void);
void delay_ms(unsigned long milliseconds);
void delay_sec(unsigned char seconds);
void timer(void);

void setupUART0(void);
void print(unsigned char *message);
void read(unsigned char *message);
void uart0(void);