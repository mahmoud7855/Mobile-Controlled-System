#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Std_Types.h"

#include "SPI_private.h"
#include "SPI_config.h"
#include "SPI_interface.h"

void SPI_voidInit()
{
    /* Clock Rate */
    #if(SPI_CLOCK_RATE == SPI_CLOCK_RATE_DIV_BY_2)
        SET_BIT(SPSR, SPSR_SPI2X);
        CLR_BIT(SPCR, SPCR_SPR1);
        CLR_BIT(SPCR, SPCR_SPR0);
        
    #elif(SPI_CLOCK_RATE == SPI_CLOCK_RATE_DIV_BY_4)
        CLR_BIT(SPSR, SPSR_SPI2X);
        CLR_BIT(SPCR, SPCR_SPR1);
        CLR_BIT(SPCR, SPCR_SPR0);

    #elif(SPI_CLOCK_RATE == SPI_CLOCK_RATE_DIV_BY_8)
        SET_BIT(SPSR, SPSR_SPI2X);
        CLR_BIT(SPCR, SPCR_SPR1);
        SET_BIT(SPCR, SPCR_SPR0);

    #elif(SPI_CLOCK_RATE == SPI_CLOCK_RATE_DIV_BY_16)
        CLR_BIT(SPSR, SPSR_SPI2X);
        CLR_BIT(SPCR, SPCR_SPR1);
        SET_BIT(SPCR, SPCR_SPR0);

    #elif(SPI_CLOCK_RATE == SPI_CLOCK_RATE_DIV_BY_32)
        SET_BIT(SPSR, SPSR_SPI2X);
        SET_BIT(SPCR, SPCR_SPR1);
        CLR_BIT(SPCR, SPCR_SPR0);

    #elif(SPI_CLOCK_RATE == SPI_CLOCK_RATE_DIV_BY_64)
        SET_BIT(SPSR, SPSR_SPI2X);
        SET_BIT(SPCR, SPCR_SPR1);
        SET_BIT(SPCR, SPCR_SPR0);

    #elif(SPI_CLOCK_RATE == SPI_CLOCK_RATE_DIV_BY_128)
        CLR_BIT(SPSR, SPSR_SPI2X);
        SET_BIT(SPCR, SPCR_SPR1);
        SET_BIT(SPCR, SPCR_SPR0);

    #endif

    /* CLOCK POLARITY */
    #if(CLOCK_POLARITY == CLOCK_POLARITY_RISING_EDGE)
        CLR_BIT(SPCR, SPCR_CPOL);
    #elif(CLOCK_POLARITY == CLOCK_POLARITY_FALLING_EDGE)
        SET_BIT(SPCR, SPCR_CPOL);
    #endif
    /* CLOCK PHASE */
    #if(CLOCK_PHASE == CLOCK_PHASE_SAMPLE)
        CLR_BIT(SPCR, SPCR_CPHA);
    #elif(CLOCK_PHASE == CLOCK_PHASE_SETUP)
        SET_BIT(SPCR, SPCR_CPHA);
    #endif
}

u8 SPI_voidTranceive (u8 Copy_u8Data)
{
    SPDR = Copy_u8Data;
    while (!GET_BIT(SPSR, SPSR_SPIF));
    return (SPDR);
}

void (* SPI_Notification)(u8 *) = NULL_POINTER;
void SPI_voidSetCallback (void (* Notification)(u8 *))
{
    SPI_Notification = Notification;
}

u8 SPI_u8StoreData = 0;
void vector_12 (void)  __attribute__((signal));
void vector_12 (void)
{
    if(SPI_Notification != NULL_POINTER)
    {
        SPI_u8StoreData = SPDR;
        SPI_Notification(&SPI_u8StoreData);
    }
    else
    {
        //Do Noting
    }
}

