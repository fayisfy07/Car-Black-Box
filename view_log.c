#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "ext_eeprom.h"

extern int log_index;
extern char event[][3];
extern char mode_f;
extern char menu_f;

char selected_index = 0; 
int read_data[5]; 
int long_press_5 = 0; 
int long_press_6 = 0; 

//Function to view the log
void view_logs()
{
    clcd_print("   SAVED LOGS   ", LINE1(0));
    char key = read_switches(LEVEL_CHANGE); //reading key pressed by the user
    
    if( log_index == 0)
    {
        //Checking if the LOG is empty
        clcd_print("   LOG EMPTY   ", LINE2(0));
    }
    else
    {
        for( int i = 0 ; i < 5 ; i++ )
        {
            //Reading data from eeprom
            read_data[i] = read_ext_eeprom((selected_index*5)+i);
            for( int wait = 100 ; wait-- ; );
        }
        
        //Printing the data on the CLCD
        clcd_putch(selected_index+48, LINE2(0)); //Prints the index
    
        clcd_putch((read_data[0]/10)+48, LINE2(2)); //Prints the hour
        clcd_putch((read_data[0]%10)+48, LINE2(3));
    
        clcd_putch(';', LINE2(4));
    
        clcd_putch((read_data[1]/10)+48, LINE2(5)); //Prints the minute
        clcd_putch((read_data[1]%10)+48, LINE2(6));
    
        clcd_putch(';', LINE2(7));
    
        clcd_putch((read_data[2]/10)+48, LINE2(8)); //Prints the seconds
        clcd_putch((read_data[2]%10)+48, LINE2(9));
    
        clcd_print(event[read_data[3]], LINE2(11)); //Prints the event
    
        clcd_putch((read_data[4]/10)+48, LINE2(14)); //Prints the speed
        clcd_putch((read_data[4]%10)+48, LINE2(15));
    }
    
    //Logic to move through the saved data
    if( key == MK_SW5 )
    {
        long_press_5++;
    }
    else if( long_press_5 > 0 && long_press_5 < 500 )
    {
        //To move up
        long_press_5 = 0;
        if( selected_index > 0 )
        {
            selected_index--;
        }
    }
    
    if( key == MK_SW6 )
    {
        //To go back to dashboard 
        long_press_6++;
        if( long_press_6 > 800 )
        {
            long_press_6 = 0;
            mode_f = MENU;
            menu_f = -1;
            selected_index = 0;
            CLEAR_DISP_SCREEN;
        }
    }
    else if( long_press_6 > 0 && long_press_6 < 800 )
    {
        //To scroll down
        long_press_6 = 0;
        if( selected_index < log_index-1 )
        {
            selected_index++;
        }
    }
    else
    {
        long_press_6 = 0;
    }
}