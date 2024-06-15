#include <xc.h>
#include "timer0.h"

void init_timer0(void)
{
	T08BIT = 1; //Selecting Timer0 as 8 bit timer
	T0CS = 0; //Selecting internal clock as source
	TMR0ON = 1; //Enabling timer0
	PSA = 1;
	TMR0 = 6; //Initalizing timer0 
	TMR0IF = 0; //Disabling timer0 flag
	TMR0IE = 1; //Enabling timer0 interrupt
}