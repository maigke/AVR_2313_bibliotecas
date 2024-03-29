/**@file adc.h
Uso de la libreria
@code #include "adc.h" @endcode

@brief

Val    REFS1 REFS0   Descripcion
 0      0     0       AREF, Vref Interno apagado (Voltaje en la terminal Aref)
 1      0     1       AVcc con capacitor externo en AREF (REferencia de 5V o alimentacion)
 2      1     0       Reservado
 3      1     1       Referencia de voltaje interna 2.56V con capacitor externo en AREF

  Valores para la conversión analogico a digital

  Canales ADC   MUX5:0
        0       0x00        ADC0  - PF0
        1       0x01        ADC1  - PF1
        4       0x04        ADC4  - PF4 -- (falso PF2)
        5       0x05        ADC5  - PF5 -- (falso PF3)
        6       0x06        ADC6  - PF6 -- (falso PF4)
        7       0x07        ADC7  - PF7 -- (falso PF5)
        8       0x20        ADC8  - PD4
        9       0x21        ADC9  - PD6
        10      0x22        ADC10 - PD7
        11      0x23        ADC11 - PB4
        12      0x24        ADC12 - Pb5
        13      0x25        ADC13 - PB6

Para leer un dato de 8 bits 
int valor;
char value;
valor = adc_read(SENSOR);
valor>>= 8; (hacer un corrimiento a la derecha para quedarse con el byte bajo;
value = (char) valor;

@author Miguel Montiel
*/

/**
@name Macros
*/

/**
@name Macros para seleccionar un solo sensor o conversion de un solo canal
*/

#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED
#define byte uint8_t

#define ADC0    0x00
#define ADC1    0x01
//#define ADC2    0x02
//#define ADC3    0x03
#define ADC4    0x04
#define ADC5    0x05
#define ADC6    0x06
#define ADC7    0x07
#define ADC8    0x20
#define ADC9    0x21
#define ADC10   0x22
#define ADC11   0x23
#define ADC12   0x24
#define ADC13   0x25
#define SENSOR  0x27

/**
@name Macro - Conversion de tipo diferencial con ganancia unitaria
* el primer canal es la entrada positiva
* el segundo canal (canal 1) es la terminal negativa
*/
#define ADC0_ADC1   0x10
#define ADC4_ADC1   0x14
#define ADC5_ADC1   0x15
#define ADC6_ADC1   0x16
#define ADC7_ADC1   0X17

/**
@name Macro -  Conversion de tipo diferencial con ganancia por 10
* el primer canal es la entrada positiva
* el segundo canal es la terminal negativa
*/
#define ADC1_ADC0_10    0x09
#define ADC4_ADC0_10    0x28
#define ADC5_ADC0_10    0x29
#define ADC6_ADC0_10    0x2A
#define ADC7_ADC0_10    0x2B

#define ADC4_ADC1_10    0x2C
#define ADC5_ADC1_10    0x2D
#define ADC6_ADC1_10    0x2E
#define ADC7_ADC1_10    0x2F

/**
@name Functions Funciones para conversion analógico a digital
*/

/**
 @fn adc_setup
 @brief funcion que permite inicializar el convertidor analógico a digital
 @param byte referencia.- Es el tipo de referencia que se va a usar para la conversion AD 
 @param byte justificacion.- Puede ser justificacion izquierda (1 - 8 bits) o derecha (0 - 10 bits) dependiendo de la resolucion de conversion
 @param unsigned int canal.- Se refiere a que canal se va a leer
 @returns none
 
   Ejemplo:
   \verbatim
   adc_setup(1,0,ADC0);
   \endverbatim                                                                     */

void adc_setup(byte referencia, byte justificacion, unsigned int canal);

/**
 @fn adc_read
 @brief funcion que devuelve la lectura del adc en funcion de los parametros establecidos
 @param unsigned char channel .-  Se le pasa como paramatro el canal o canales a leer
 @returns unsigned int devuelve un entero sin signo, ya que puede ser un valor de 8 o de 10 bits
 
   Ejemplo:
   \verbatim
   valor = adc_read(SENSOR);
   \endverbatim                                                                     */

unsigned int adc_read(unsigned char channel);

#endif // ADC_H_INCLUDED
