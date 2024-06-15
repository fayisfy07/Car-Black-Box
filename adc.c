#include <xc.h>
#include "adc.h"


//Function to initazlie ADC
void init_adc( void )
{
    ADON = 1;
    
    VCFG1 = 0;
    VCFG0 = 0;
    
    PCFG3 = 1;
    PCFG2 = 0;
    PCFG1 = 1;
    PCFG0 = 0;
    
    ADFM = 0;
    
    ACQT2 = 1;
    ACQT1 = 0;
    ACQT0 = 0;
    
    ADCS2 = 0;
    ADCS1 = 1;
    ADCS0 = 0;
}


//Function to read value from analog peripheral from selected channel via ADC
unsigned short int read_adc( unsigned char channel )
{
    ADCON0 = ( ADCON0 & 0xc3) | ( channel << 2 );
    
    GO = 1;
    
    while( GO );
    
    return ( ADRESH << 2) | ( (ADRESL & 0xc0) >> 6);
}