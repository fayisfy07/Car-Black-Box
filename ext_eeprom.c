#include <xc.h>
#include "i2c.h"
#include "ext_eeprom.h"

//Function to write data to the external EEPROM
void write_ext_eeprom(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(SLAVE_WRITE_EEPROM);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
    for( int i = 3000 ; i--; );
}

//Function to read data from the external EEPROM
unsigned char read_ext_eeprom(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(SLAVE_WRITE_EEPROM);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(SLAVE_READ_EEPROM);
	data = i2c_read();
	i2c_stop();

	return data;
}