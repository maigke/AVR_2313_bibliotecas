#ifndef __UART_H
#define __UART_H

//#define F_CPU 16000000L
#include "clk.h"
#include <stdio.h>

# define USART_BAUDRATE 9600UL
# define BAUD_PRESCALE ((( F_CPU / ( USART_BAUDRATE * 16UL))) - 1)

//definicion de teclas
#define INTRO 0x0D
#define RETROCESO 0x08
#define ESCAPE 0x1B

//define el tamano del buffer
#define lenbuff 10

/* Macros para AVR GCC */
#if defined( __GNUC__ )
#ifdef putchar
#undef putchar
#endif
#ifdef getchar
#undef getchar
#endif
#endif

/* Definiciones de funciones */
int putchar(int);
int getchar(void);


void uart_transmit( unsigned char data );
unsigned char uart_receive(void);
void uart_init(void);
int uart_dataAvailable(void);
void uart_print(const char *s);
/**
* funcion que limpia el buffer de caracteres para la comunicacion serial
*/
void initBuff(void);
/**
* funcion para agregar un caracter al buffer de comunicacion serial
*/
void add2cbuff(unsigned char c);

/**
* funcion que imprime un echo a la terminal, solo caracteres imprimibles
*/
void echosel(unsigned char c);


#endif
