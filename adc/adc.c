#include <avr/io.h>
#if defined(__AVR_ATmega32U4__)
    #include "clk.h"
#endif
#include <util/delay.h>
#include "adc.h"

void adc_setup( byte referencia, byte justificacion, unsigned int canal)
{

	byte temp1=0;
	byte temp2=0;

	referencia&=3;
	justificacion&=1;
	canal&=0x2F;


	//Deshabilitación de la entrada digital
	if(canal < 8)
        DIDR0|=(1<<canal);
    if(canal <13 && canal >7)
    {
        temp1 = (canal & 0x08);
        temp2 = (canal & 0x07);
        DIDR1 = (temp1 << 5) | (temp2);
    }


	ADMUX=(referencia<<6)|(justificacion<<5)|(canal&0x1F);
	ADCSRA=(1<<ADEN)|(ADC_PRESCALER); //adc habilitado por defecto
	ADCSRA&=~(1<<ADATE); //modo manual
	ADCSRB=((canal&0x20));
}

unsigned int adc_read(unsigned char channel)
{
    ADMUX&=0xE0;
    ADCSRB&=0xCF;
    _delay_us(10);
    ADMUX|= (channel&0x1F);
    ADCSRB|=(channel&0x20);

    ADCSRA|=(1<<ADSC); //Se inicia la conversion

    while(bit_is_clear(ADCSRA,ADIF)); //Espera a que termine la conversiom
    return ADC;
}
