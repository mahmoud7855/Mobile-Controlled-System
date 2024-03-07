#include <util/delay.h>

#include "../../LIB/Std_Types.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/TIMER/TIMER_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/GIE/GIE_interface.h"

#include "ULTRA_private.h"
#include "ULTRA_config.h"
#include "ULTRA_interface.h"


void ULTRA_voidInit()
{
    TIMER_voidTimer1Init();
    GIE_voidEnableGlobalInterrupt();
    ICU_voidControlInterrupt(ENABLE);
    ICU_voidSenceModetrigger(RISING_EDGE);

    DIO_voidSetPinDirection(ECHO_PORT, ECHO_PIN, INPUT);
    DIO_voidSetPinDirection(TRIG_PORT_SELECTION, TRIG_PIN_SELECTION, OUTPUT);
}

u16 ULTR_u16Calculations(void)
{
    volatile u16 ON          = 0;
    volatile u16 Duration    = 0;
    volatile u16 Distance    = 0;
    volatile u16 A1_Reading  = 0;
    volatile u16 A2_Reading  = 0;

    //Clear Flag
    SET_BIT(TIFR, TIFR_ICF1);

    //Trig Ultrasonic To Work
    DIO_voidSetPinValue(TRIG_PORT_SELECTION, TRIG_PIN_SELECTION, LOW);
    _delay_us(2);
    DIO_voidSetPinValue(TRIG_PORT_SELECTION, TRIG_PIN_SELECTION, HIGH);
    _delay_us(10);
    DIO_voidSetPinValue(TRIG_PORT_SELECTION, TRIG_PIN_SELECTION, LOW);

    ICU_voidSenceModetrigger(RISING_EDGE);
    while (GET_BIT(TIFR, TIFR_ICF1) == 0);
    A1_Reading = ICR1;
    SET_BIT(TIFR, TIFR_ICF1);

    ICU_voidSenceModetrigger(FALLING_EDGE);
    while (GET_BIT(TIFR, TIFR_ICF1) == 0);
    A2_Reading = ICR1;
    SET_BIT(TIFR, TIFR_ICF1);
    TCNT1 = 0;
    ICU_voidControlInterrupt(DISABLE);

    ON = A2_Reading - A1_Reading;
    Distance = (ON* 34600)/(8000000*2);


    return(Distance);
}
