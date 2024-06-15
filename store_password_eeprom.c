#include <xc.h>
#include "main.h"
#include "ext_eeprom.h"

//Function to write the password to the external EEPROM
void store_password( char *pwd )
{
    write_ext_eeprom(200, pwd[0]);
    write_ext_eeprom(201, pwd[1]);
    write_ext_eeprom(202, pwd[2]);
    write_ext_eeprom(203, pwd[3]);
}