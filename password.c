#include<xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"

extern char mode_f;
extern unsigned short timer_count;

char user_input[PASS_SIZE]; 
char lock_flag = 0; 
char index = 0; 
unsigned int delay = 0; //Variable for flag
char lock_delay = 0; //Delay for locking the system


void password() 
{   
    char password[5]; //Array to store the password read from the EEPROM
    
    read_password_eeprom( password); //Reads the password from the EEPROM
    
    if( lock_flag < 3 )
    {
        if( index < 4 )
        {
            //user can enter 3 times the password
            clcd_print(" ENTER PASSWORD ", LINE1(0));
            
            unsigned char key = read_switches(STATE_CHANGE);
            //Condition to blink the current field
            if( delay == 500 ) 
            {
                clcd_putch('_', LINE2(6+index));
            }
            else if( delay == 1000 )
            {
                delay = 0;
                clcd_putch(' ', LINE2(6+index));
            }
            delay++;
        
            //Entering the password
            if( key == MK_SW5 )
            {
                user_input[index] = '0';
                clcd_putch('*', LINE2(6+index));
                index++;
            }
            else if( key == MK_SW6 )
            {
                user_input[index] = '1';
                clcd_putch('*', LINE2(6+index));
                index++;
            }
        }
        else if( index == 4)
        {
            //After password has been entered, checking the password
            if( password_compare(user_input, password) == 1)
            {
                //On success, enter the menu
                mode_f = MENU;
                lock_flag = 0; //Resetting lock flag
                index = 0;
            }
            else
            {
                //If password is not correct
                lock_flag++;
                if( lock_flag <3 )
                {
                    for( int wait = 2000 ; wait-- ; )
                    {
                        clcd_print(" WRONG PASSWORD ", LINE1(0));
                        clcd_putch((3-lock_flag)+48, LINE2(0));
                        clcd_print(" Attempt remain", LINE2(1));
                    }
                }
                index = 0;
                lock_delay = 180; //Initializing a 180 second delay
                timer_count = 0; //Resetting the timer counter
                CLEAR_DISP_SCREEN;
            }
        }
    }
    else if( lock_flag == 3 )
    {
        /* When the password is wrong at 3rd attempt, 
        lock the system for 180 seconds */
        
        if( lock_delay > 0 )
        {
            clcd_print(" SYSTEM  LOCKED ", LINE1(0));
            clcd_print(" TRY AFTER ", LINE2(0));
            clcd_putch((lock_delay/100)+48,LINE2(11));
            clcd_putch(((lock_delay/10)%10)+48,LINE2(12));
            clcd_putch((lock_delay%10)+48,LINE2(13));
            clcd_putch('s',LINE2(14));
        }
        else if( lock_delay == 0 )
        {
            //After 180 seconds, unlock the device
            lock_flag = 0;
            CLEAR_DISP_SCREEN;
            mode_f = DASHBOARD;
        }
    }
    
}

//Function to compare the passwords
char password_compare( char *key , char *pwd)
{
    //Function to compare the passwords
    for( char i = 0 ; i < 4 ; i++ )
    {
        if( pwd[i] != key[i] )
        {
            return 0;
        }
    }
    return 1;
}