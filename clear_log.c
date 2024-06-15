#include <xc.h>
#include "ext_eeprom.h"
#include "main.h"
#include "clcd.h"

extern int log_index;
extern int log_loc;
extern char mode_f;
extern char menu_f;

//clear the log from the eeprom
void clear_log()
{
    //Iniailized the log index as zero and store the event
    log_index = 0;
    log_loc = 0;
    store_event(8);
    
    
    for( int wait = 2500 ; wait-- ; )
    {
        clcd_print("  LOGS CLEARED  ", LINE1(0));   //printing the log has been cleared
    }
    CLEAR_DISP_SCREEN;
    
    //Re-setting mode back to dashboard mode
    mode_f = MENU;
    menu_f = -1;
}