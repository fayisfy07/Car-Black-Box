#include <xc.h>
#include "eeprom.h"
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"

extern char menu_f;
extern char mode_f;

char new_pass[PASS_SIZE]; //array for storing new password
char new_pass_re[PASS_SIZE]; //array to re_check the password
int blink = 0; //for blinking the current occurence
int pass_index = 0; //Variable to move through the index
int pass_flag = 0; //Variable for re-entering the password


//Function to change the password
void change_pass(char key)
{
//    char key = read_switches(STATE_CHANGE); //Reading the key pressed by the user
    
    if( pass_flag == 0 )
    {
        clcd_print(" ENTER NEW PASS ", LINE1(0));
    }
    else if( pass_flag == 1)
    {
        clcd_print("RE-TYPE NEW PASS", LINE1(0));
    }
    
    //Condition to blink the current field
    if( blink == 500 && pass_flag != 2 )
    {
        clcd_putch('_', LINE2(6+pass_index));
    }
    else if( blink == 1000 && pass_flag != 2 )
    {
        blink = 0;
        clcd_putch(' ', LINE2(6+pass_index));
    }
    blink++;
    
    if( pass_index < 4 )
    {
        if( key == MK_SW5 )
        {
            if( pass_flag == 0 )
            {   
                new_pass[pass_index] = '0';
            }
            else
            {
                new_pass_re[pass_index] = '0';
            }
            clcd_putch('*', LINE2(6+pass_index));
            pass_index++;
        }
        else if( key == MK_SW6 )
        {
            if( pass_flag == 0 )
            {   
                new_pass[pass_index] = '1';
            }
            else
            {
                new_pass_re[pass_index] = '1';
            }
            clcd_putch('*', LINE2(6+pass_index));
            pass_index++;
        }
    }
    else if( pass_index == 4 && pass_flag == 0 )
    {
        pass_index = 0;
        pass_flag++;
        CLEAR_DISP_SCREEN;
    }
    else if( pass_index == 4 && pass_flag == 1 )
    {
        pass_flag++;
    }
    else if( pass_index == 4 && pass_flag == 2)
    {
        // for Compare the passwords
        CLEAR_DISP_SCREEN;
        clcd_print("PASSWORD  CHANGE", LINE1(0));
        if( password_compare(new_pass, new_pass_re) == 1 )
        {
            //Print the success message, store the new password and return to menu
            for( int wait = 3000 ; wait -- ;)
            {
                clcd_print("   SUCCESSFUL   ", LINE2(0));
            }
            
            store_password(new_pass);
            store_event(9);
        }
        else
        {
            //Print error message and return to menu
            for( int wait = 3000 ; wait -- ;)
            {
                clcd_print("    FAILURE     ", LINE2(0));
            }
        }
        
        pass_index = 0;
        pass_flag = 0;
        
        CLEAR_DISP_SCREEN;
        mode_f = MENU; //Setting mode flag to menu to return back to menu
        menu_f = -1;
    }
}