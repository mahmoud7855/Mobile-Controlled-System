#ifndef _ULTRA_PRIVATE_H
#define _ULTRA_PRIVATE_H

#define     TCCR1A              *((volatile u8 *)(0x4F))		// Timer/Counter1 A Control Register

#define     TCCR1B              *((volatile u8 *)(0x4E))		// Timer/Counter 1 B Control Register


#define     TCNT1               *((volatile u16 *)0x4C)         // Timer/Counter 1 Regsiter
#define     ICR1                *((volatile u16 *)0x46)         // Timer/Counter 1 Input Capture Register

#define     TIFR                *((volatile u16 *)0x58)
#define     TIFR_ICF1           BIT_5

#define     ECHO_PORT           PORTD
#define     ECHO_PIN            PIN6


#endif