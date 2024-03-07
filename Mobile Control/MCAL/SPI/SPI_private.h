#ifndef _SPI_PRIVATE_H
#define _SPI_PRIVATE_H


#define SPCR                                      *((volatile u8 *)0x2D)
#define SPCR_SPR0                                 BIT_0
#define SPCR_SPR1                                 BIT_1
#define SPCR_CPHA                                 BIT_2
#define SPCR_CPOL                                 BIT_3
#define SPCR_MSTR                                 BIT_4
#define SPCR_DORD                                 BIT_5
#define SPCR_SPE                                  BIT_6
#define SPCR_SPIE                                 BIT_7


#define SPSR                                      *((volatile u8 *)0x2E)
#define SPSR_SPI2X                                BIT_0
#define SPSR_WCOL                                 BIT_6
#define SPSR_SPIF                                 BIT_7



#define SPDR                                      *((volatile u8 *)0x2F)


#define SPI_CLOCK_RATE_DIV_BY_2                    0 
#define SPI_CLOCK_RATE_DIV_BY_4                    1
#define SPI_CLOCK_RATE_DIV_BY_8                    2 
#define SPI_CLOCK_RATE_DIV_BY_16                   3
#define SPI_CLOCK_RATE_DIV_BY_32                   4 
#define SPI_CLOCK_RATE_DIV_BY_64                   5
#define SPI_CLOCK_RATE_DIV_BY_128                  6

#define CLOCK_POLARITY_RISING_EDGE                0
#define CLOCK_POLARITY_FALLING_EDGE               1


#define CLOCK_PHASE_SAMPLE                        0
#define CLOCK_PHASE_SETUP                         1

#endif