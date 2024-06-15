/*   
 * Name : Mohammed Fayis
 * Regn No. : 23029_052
 * Project Title: Car Black Box
 */

#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "ext_eeprom.h"
#include "matrix_keypad.h"
#include "timer0.h"
#include "i2c.h"
#include "RTC.h"
#include "uart.h"


void init_config()
{
    init_adc(); 
    init_matrix_keypad(); //initializing the matrix key_pad
    init_clcd();        //initializing the clcd
    init_timer0(); 
    init_i2c(); 
    init_rtc(); 
    init_uart(); 
    
    GIE = 1; 
    
    store_password("1001");     //store the password in EEPROM
    store_event(0);
}

char time[TIME_ARR_SIZE] = {'0', '0', ':', '0', '0', ':', '0', '0', '\0'}; 
char event[EVENT_ARR_SIZE][3] = { "ON", "GR", "GN", "G1", "G2", "G3", "-C", "DL", "CL", "CP", "ST" };
char event_flag = 0; 
char mode_f = 0; //flag for dashboard, initialized as dashboard 
char menu_f = -1; //flag to select menu content

void main(void) 
{
    char key; //var to store the key pressed
    char col_flag = 0; //flag to check for collision
    
    init_config();
    
    while(1)
    {
        key = read_switches(STATE_CHANGE);

        //To display the modes
        if( mode_f == DASHBOARD )
        {
            dashboard();  //Dashboard mode
        }
        else if( mode_f == PASSWORD )
        {
            password();
        }
        else if( mode_f == MENU )
        {
            //Display the menu
            menu();
        }
        else if( mode_f == MENU_ENTER )
        {
            if( menu_f == VIEWLOG )
            {
                //Function to view the log on the CLCD
                view_logs();
            }
            else if( menu_f == DOWNLOADLOG )
            {
                //Function to download the log
                download_log();
            }
            else if( menu_f == CLEARLOG )
            {
            
                //function to clear the log
                clear_log();
            }
            else if( menu_f == SETTIME )
            {
                //Function to change the time in the RTC
                settime();
            }
            else if( menu_f == CHANGEPASS )
            {
                //Function to change the password
                change_pass(key);
            }
        }
        
        //event detection occur
        
        if( key == MK_SW2 && col_flag == 0) 
        {
            if( event_flag < 5 )
            {
                event_flag++;
                store_event(event_flag);
            }
        }
        else if( key == MK_SW2 && col_flag == 1 ) 
        {
            col_flag = 0;
            event_flag = 2;
            store_event( event_flag );
        }
        else if( key == MK_SW3 && col_flag == 0) 
        {
            if( event_flag > 1 )
            {
                event_flag--;
                store_event( event_flag );
            }
        }
        else if( key == MK_SW3 && col_flag == 1 ) 
        {
            col_flag = 0;
            event_flag = 2;
            store_event( event_flag );
        }
        else if( key == MK_SW1 ) 
        {
            col_flag = 1;
            event_flag = 6; 
            store_event( event_flag );
        }
        
        //Mode changes
        if( key == MK_SW5 && mode_f == DASHBOARD)
        {
            mode_f = PASSWORD;
            CLEAR_DISP_SCREEN;
        }
    }
}