#include "RTC.h"
#include "i2c.h"
#include <xc.h>

//Function to Initalize the RTC
void init_rtc(void)
{
	unsigned char dummy;

	/* Setting the CH bit of the RTC to Stop the Clock */
	dummy = read_ds1307(SEC_ADDR);
    write_ds1307(SEC_ADDR, dummy&0x7f );
	//write_ds1307(SEC_ADDR, dummy | 0x80); 

	/* Seting 24 Hr Format */
	dummy = read_ds1307(HOUR_ADDR);
	write_ds1307( HOUR_ADDR, dummy | 0x00); 

}

//Function to write data to the RTC
void write_ds1307(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(SLAVE_WRITE_RTC);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
}

//Function to read data from the RTC
unsigned char read_ds1307(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(SLAVE_WRITE_RTC);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(SLAVE_READ_RTC);
	data = i2c_read();
	i2c_stop();

	return data;
}