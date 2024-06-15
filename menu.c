#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"
#include "main.h"

extern char mode_f;
extern char menu_f;


char menu_options[5][17] = {"View Logs      ", "Download Log   ","Clear Log      ","Set Time       ","Change Password  "};
char option = 0;   //to point the currently selected option of menu
char star = 0; //flag to show which line the star symbol is printing
char print_f = 0; //flag to display in clcd 
int long_press_SW5 = 0; //for detecting long press on switch 5
int long_press_SW6 = 0; //for detecting long press on switch 6

//function to display the selected menu
void menu()
{
    char key; //var to store the key pressed
    
    key = read_switches(LEVEL_CHANGE);  //reading the key
    
    clcd_print(menu_options[print_f], LINE1(1));    //printing on clcd
    clcd_print(menu_options[print_f+1], LINE2(1));
    
    //print the star on selected option and line
    if( star == 0 )     
    {
        clcd_putch('*', LINE1(0));
        clcd_putch(' ', LINE2(0));
    }
    else
    {
        clcd_putch('*', LINE2(0));
        clcd_putch(' ', LINE1(0));
    }
    
    if( key == MK_SW5 )
    {
        long_press_SW5++;
        
        if( long_press_SW5 > 800 )
        {
          
            long_press_SW5 = 0;
            mode_f = MENU_ENTER; 
            menu_f = option;
            CLEAR_DISP_SCREEN;
            
            print_f = 0;
            star= 0;
            option = 0;
        }
    }
    else if( long_press_SW5 > 0 && long_press_SW5 < 800 )
    {
        //to go up
        long_press_SW5 = 0;
        if( star == 1)
        {
            star = 0;
            option--;
        }
        else if( option > 0)
        {
            option--;
            print_f--;
        }
    }
    else
    {
        long_press_SW5 = 0;
    }
    
    if( key == MK_SW6 )
    {
        long_press_SW6++;
        if( long_press_SW6 > 800)
        {
           
            long_press_SW6 = 0; //to go back to dashboard
            CLEAR_DISP_SCREEN;
            mode_f = DASHBOARD;
            menu_f = -1;
            
            print_f = 0;
            star = 0;
            option = 0;
            
            if( mode_f == SETTIME )
            {
               
                get_time(); 
            }
        }
    }
    else if( long_press_SW6 > 0 && long_press_SW6 < 800 )
    {
        //to go down
        long_press_SW6 = 0;
        if( star == 0 )
        {
            star = 1;
            option++;
        }
        else if( option > 0 && option < 4)
        {
            option++;
            print_f++;
        }
    }
    else
    {
        long_press_SW6 = 0;
    }
}