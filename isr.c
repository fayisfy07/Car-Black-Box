#include <xc.h>

extern char lock_delay;
unsigned short timer_count;

void __interrupt() isr(void)
{
     
	if (TMR0IF) //Checking for Timer0
	{
		TMR0 = TMR0 + 8;

		if (timer_count++ == 20000)
		{
			timer_count = 0;
			lock_delay--;
		}
		TMR0IF = 0;
	}
}