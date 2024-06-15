#include<xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "RTC.h"

extern char time[TIME_ARR_SIZE];
extern char event[EVENT_ARR_SIZE][3];
extern char event_flag;

unsigned char clock_reg[3];
unsigned short speed; //Variable to store the value of Speed

//to obtain the time from the RTC
void get_time(void)
{   
    //Reading data from the RTC
	clock_reg[0] = read_ds1307(HOUR_ADDR); 
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

    //Storing the data to time array for printing on CLCD
    time[0] = '0' + ((clock_reg[0] >> 4) & 0x03); 
    time[1] = '0' + (clock_reg[0] & 0x0F);
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}


//Function to print the details on the dashboard
void dashboard( void )
{
    //Printing the dashboard mode
    clcd_print("  TIME    EV  SP", LINE1(0)); //dashboard interface details printing
    
    unsigned short adc_val; //Variable to store the value read from the POT
    
    adc_val = read_adc(CHANNEL4); //Reading the POT value 
    speed = adc_val/10.23; //Obtains the speed value based on the value read from POT
    get_time(); //Obtains the time from the RTC
    
    //Printing the data time,event and speed
    clcd_print(time, LINE2(0)); 
    clcd_print(event[event_flag], LINE2(10)); 
    clcd_putch((speed/10)+48, LINE2(14)); 
    clcd_putch((speed%10)+48, LINE2(15));
    
}