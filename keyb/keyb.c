/************************************************************************
@file "keyb.c"
Implementación del modulo keyb.h
@author Miguel Montiel
************************************************************************/
#include <avr/io.h>
#include "clk.h"
#include "keyb.h"
/**
@details Inicializa como salidas a PORT_KEY_Rx y como entradas a PORT_KEY_Cx
se escribe tambien a PORT_KEY_Cx un valor alto con la finalidad de habilitar las
reistencias de pull up 
*/
void vInitKeyPad(void)
{
	//Se configuran entradas
	clrbit(DDR(PORT_KEY_C1),PIN_KEY_C1);
	clrbit(DDR(PORT_KEY_C2),PIN_KEY_C2);
	clrbit(DDR(PORT_KEY_C3),PIN_KEY_C3);
	clrbit(DDR(PORT_KEY_C4),PIN_KEY_C4);
	//Se configuran salidas
	setbit(DDR(PORT_KEY_R1), PIN_KEY_R1);
	setbit(DDR(PORT_KEY_R2), PIN_KEY_R2);
	setbit(DDR(PORT_KEY_R3), PIN_KEY_R3);
	setbit(DDR(PORT_KEY_R4), PIN_KEY_R4);
	
	//Habilitando las resistencias de pullup
	setbit(PORT_KEY_C1, PIN_KEY_C1);
	setbit(PORT_KEY_C2, PIN_KEY_C2);
	setbit(PORT_KEY_C3, PIN_KEY_C3);
	setbit(PORT_KEY_C4, PIN_KEY_C4);
}

/**
@details comienza por asignar a una variable k un cero y la va "girando" por las filas y lee el valor de las columnas
con la finalidad de saber el valor de k o tecla presionada, el cual devuelve
*/

unsigned char ui8_TestKeyPad()
{
	unsigned char k;
	for(k=0;k<16;k++)
	{
		switch(k)
		{
			case 0: vSetKeyPadR1();
			break;
			case 4: vSetKeyPadR2();
			break;
			case 8: vSetKeyPadR3();
			break;
			case 12: vSetKeyPadR4();
			break;
			default: vSetKeyPad();
		}
		
		
		if (!(PIN(PORT_KEY_C1) & (1 << PIN_KEY_C1)))
		{
			delay_ms(20);
			if (!(PIN(PORT_KEY_C1) & (1 << PIN_KEY_C1)))
			{vSetKeyPad();
			return k;
			}			
		} k++;
		
		if (!(PIN(PORT_KEY_C2) & (1 << PIN_KEY_C2)))
		{
			delay_ms(20);
			if (!(PIN(PORT_KEY_C2) & (1 << PIN_KEY_C2)))
			{vSetKeyPad();
				return k;
			}
		}k++;
		
		if (!(PIN(PORT_KEY_C3) & (1 << PIN_KEY_C3)))
		{
			delay_ms(20);
			if (!(PIN(PORT_KEY_C3) & (1 << PIN_KEY_C3)))
			{vSetKeyPad();
				return k;
			}
		}k++;
		
		if (!(PIN(PORT_KEY_C4) & (1 << PIN_KEY_C4)))
		{
			delay_ms(20);
			if (!(PIN(PORT_KEY_C4) & (1 << PIN_KEY_C4)))
			{vSetKeyPad();
				return k;
			}
		}
	}
	vSetKeyPad();
	return (16);
}