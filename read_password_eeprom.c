#include <xc.h>
#include "main.h"
#include "ext_eeprom.h"

//Function to read the password saved in the external EEPROM
void read_password_eeprom( char *password )
{
    password[0] = read_ext_eeprom(200);
    password[1] = read_ext_eeprom(201);
    password[2] = read_ext_eeprom(202);
    password[3] = read_ext_eeprom(203);
}