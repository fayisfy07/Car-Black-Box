#include<xc.h>
#include "main.h"
#include "ext_eeprom.h"

extern unsigned short speed;
extern char time[9];

int log_index = 0; //Variable to count the number of events stored
int log_loc = 0; //Variable to hold the writing address

//Function to store the event to the External EEPROM
void store_event( int event_index )
{
    int log_data[5]; //Array to store the data temporarily
    
    get_time(); //Storing the current time to time array ( In case mode is not in DASHBOARD)
    
    log_data[0] = ( time[0] - 48 )*10 + (time[1] - 48); //Storing hour
    log_data[1] = ( time[3] - 48 )*10 + (time[4] - 48); //Storing minute
    log_data[2] = ( time[6] - 48 )*10 + (time[7] - 48); //Storing hour*/
    
    log_data[3] = event_index; //Storing the event flag
    
    log_data[4] = speed; //Storing the speed
    
    
    //Storing the data to the external EEPROM
    for( int i = 0 ; i < 5 ; i++ )
    {
        write_ext_eeprom((log_loc*5)+i, log_data[i]);
        for( int wait = 100 ; wait-- ; );
    }
    
    //Updating the index of log
    if( log_index != 10 )
    {
        log_index++;
    }
    
    log_loc++;
    if( log_loc == 10)
    {
        //After 10 logs have been saved, restart and over write from the beginning
        log_loc = 0;
    }
}