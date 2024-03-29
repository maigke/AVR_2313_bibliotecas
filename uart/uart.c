// uart.c
// Originally for NerdKits with ATmega168, 14.7456 MHz clock
// mrobbins@mit.edu
// Modified for Adafruit ATMega32u4 Breakout, with 16.0000Mhz clock
// Note, this references serial 1, not 0, since the micro does not have 0.
// At least for the above breakout, D3 is TX, and D2 RX
// https://github.com/tomvdb/avr_arduino_leonardo/blob/master/examples/uart/main.c

#include "clk.h"
#include <avr/io.h>
#include <string.h>
#include "uart.h"
#include <util/delay.h>

//variables para el manejo de comunicacion serial
typedef enum{false, true} boolean;
boolean flagcommand= false;
unsigned char xbuff=0x00;
unsigned char cbuff[lenbuff];
char rcvchar=0x00;



// init uart
void uart_init(void)
{
    // set baud rate
    unsigned int baud = BAUD_PRESCALE;

    UBRR1H = (unsigned char)(baud >> 8 );
    UBRR1L = (unsigned char)baud;
    //UBRR1H = 0;
    //UBRR1L = 0x34;

    // enable received and transmitter
    UCSR1B = ( 1 << RXEN1 ) | ( 1 << TXEN1 );

    // set frame format ( 8data, 2stop )
    UCSR1C = ( 1 << USBS1 ) | ( 1 << UCSZ11 ) | (1 << UCSZ10);

    /* Descomentar el siguiente #define para que la funcion 'getchar' haga eco de
* los caracteres recibidos.
*/
#define __GETCHAR_ECHO__

#if defined( __GNUC__ )
    /* Asociar las funciones 'putchar' y 'getchar' con las funciones de entrada
    * y salida (como printf, scanf, etc.) de la librería 'stdio' de AVR-GCC */
    fdevopen((int (*)(char, FILE*))putchar, (int (*)(FILE*))getchar);
#endif
}


//****************************************************************************
// Transmite el byte bajo de 'dato' por el USART
//****************************************************************************
int putchar(int dato)
{
    /* Esperar a que haya espacio en el buffer de transmisión */
    while ((UCSR1A & (1<<UDRE1)) == 0 );

    /* Colocar dato en el buffer de transmisión */
    UDR1 = dato;
    return dato;
}


//****************************************************************************
// Recibe un byte de dato del USART
//****************************************************************************
int getchar(void)
{
    /* Esperar a que haya al menos un dato en el buffer de recepción */
    while ((UCSR1A & (1<<RXC1)) == 0 );

    /* Leer y retornar el dato menos reciente del buffer de recepción */
#if defined ( __GETCHAR_ECHO__ )
    return (putchar(UDR1));
#else
    return UDR1;
#endif
}


// transmit a char to uart
void uart_transmit( unsigned char data )
{
    // wait for empty transmit buffer
    while ( ! ( UCSR1A & ( 1 << UDRE1 ) ) )
        ;

    // put data into buffer, sends data
    UDR1 = data;
}

// read a char from uart
unsigned char uart_receive(void)
{
    while (!( UCSR1A & ( 1 << RXC1) ))
        ;

    return UDR1;
}



// check if there are any chars to be read
int uart_dataAvailable(void)
{
    if ( UCSR1A & ( 1 << RXC1) )
        return 1;

    return 0;
}

// write a string to the uart
void uart_print(const char *s)
{
    register char c;
    while((c=*s++)){
        uart_transmit(c);
    }
}
/*
void uart_print( char data[] )
{
    int c = 0;

    for ( c = 0; c < strlen(data); c++ )
        uart_transmit(data[c]);
}
*/

void initBuff(void)
{
    int i;
    for(i=0;i<lenbuff; i++)
    {
        cbuff[i]=0x00;
    }xbuff=0x00;
}

void add2cbuff(unsigned char c)
{
    if(xbuff<lenbuff)
    {
        switch(c)
        {
        case INTRO:
            flagcommand = true;
            break;
        case RETROCESO:
            if(xbuff>0) cbuff[--xbuff] = 0x00;
            break;
        case ESCAPE:
            initBuff();
            break;
        default:
            cbuff[xbuff++]=c;
        }
    }
    else
    {
        initBuff();
        uart_print("ERROR\r\n");
    }
}

void echosel(unsigned char c)
{
    switch(c)
    {
    case INTRO:
        uart_print("\r\n");
        break;
    case RETROCESO:
        uart_transmit(RETROCESO);
        break;
    case ESCAPE:
        uart_transmit(ESCAPE);
        break;
    default:
        uart_transmit(c);
    }
}
