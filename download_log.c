#include <xc.h>
#include "clcd.h"
#include "main.h"
#include "uart.h"
#include "ext_eeprom.h"

extern int log_index;
extern char mode_f;
extern char menu_f;
extern char event[EVENT_ARR_SIZE][3];

int logged_data[5]; //Array to store the data read from the EEPROM

//Function to download log from the EEPROM and display on the clcd
void download_log()
{
 
    int curr_index = 0; 
    
    for( int wait = 500 ; wait-- ;)
    {
        clcd_print("DOWNLOADING LOGS", LINE1(0));
    }
    
    store_event(7); //Storing the event to the external EEPROM
    
    puts("\rSAVED LOGS\n\r");
  
    if( log_index == 0)
    {
        //If no logs are saved in the EEPROM
        puts("NO SAVED LOGS\n\r");
    }
    else
    {
        puts("Index\t  Time\t   Event\tSpeed\t\n\r");
    }
    //Loop to obtain the data from external EEPROM
    while( curr_index < log_index )
    {
        for( int i = 0 ; i < 5 ; i++ )
        {
            logged_data[i] = read_ext_eeprom((curr_index*5)+i);
            for( int delay = 100 ; delay-- ;);
        }
        
        //Displaying the data on the clcd
        puts("  ");
        putch((curr_index%10)+48);
        
        putch('\t');
        
        putch((logged_data[0]/10)+48); //Prints the hour
        putch((logged_data[0]%10)+48);
        
        putch(':');
        
        putch((logged_data[1]/10)+48); //Prints the minute
        putch((logged_data[1]%10)+48);
        
        putch(':');
        
        putch((logged_data[2]/10)+48); //Prints the second
        putch((logged_data[2]%10)+48);
        
        puts("    ");
        
        
        puts(event[logged_data[3]]); //Prints the event
        
        puts("\t\t ");
        
        putch((logged_data[4]/10)+48); //Prints the speed
        putch((logged_data[4]%10)+48);
        
        putch('\n');
        putch('\r');
        curr_index++;
    }
    
    for( int wait = 2500 ; wait-- ; )
    {
        clcd_print("  DOWNLOAD LOG  ", LINE1(0));
        clcd_print("   SUCCESSFUL   ", LINE2(0));
    }
    
    //After printing all the data, go back to menu
    mode_f = MENU;
    menu_f = -1;
    CLEAR_DISP_SCREEN;
    
}