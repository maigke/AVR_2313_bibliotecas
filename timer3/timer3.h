/**
@code #include <timer3.h> @endcode

@brief
Rutina para la configuración del timer 3 de 16 bits
Este temporizador cuenta con 16 modos de operación clasificados en 5 grupos

* Normal                                        modo{0}
* CTC (limpia a la captura)                     modo{4,12}
* Fast PWM                                      modo{5,6,7,14,15}
* PWM de Fase Correcta                          modo{1,2,3,10,11}
* PWM de fase correcta, frecuencia correcta     modo{8,9}
*/


#ifndef TIMER3_H_INCLUDED
#define TIMER3_H_INCLUDED
#define byte uint8_t

void timer3_setup(byte mode, int prescale, unsigned char outmode_A, unsigned char outmode_B, unsigned char capture);

#endif // TIMER3_H_INCLUDED
