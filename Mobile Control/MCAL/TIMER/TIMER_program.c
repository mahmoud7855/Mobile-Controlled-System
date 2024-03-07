/***********************************************************************
 * Auther: Mahmoud G. Mahmoud
 * Creation date: 20 Oct, 2023
 * Version: v2.0 
 * Compiler: 
 * Controller: ATMEGA32
 * Leyer: MCAL
 ***********************************************************************/
/***********************************************************************
 * Version    Date                    Auther            Description
 * v2.0       20 Oct, 2023      Mahmoud G. Mahmoud      
***********************************************************************/


/*Library Inclusion*/
#include "../../LIB/Std_Types.h"
#include "../../LIB/BIT_MATH.h"

/*Lower Layer Inclusion*/


/*Self Layer Inclusion*/
#include "../DIO/DIO_interface.h"
#include "../GIE/GIE_interface.h"

/*Self Files Inclusion*/
#include "TIMER_private.h"
#include "TIMER_interface.h"
#include "TIMER_config.h"



         

void TIMER_voidTimer0Init(void)
{
    TCCR0 &= TIMER_PRESCALER_MASK_CLR;
    TCCR0 |= TIMER_COUNTER_PRESCALER_SELECT;

    TCCR0 &= TIMER0_SELECT_MODE_MASK_CLR;
    TCCR0 |= TIMER0_MODE;

    TCCR0 &= TIMER_SUB_MODE_MSK_CLR;
    TCCR0 |= TIMER0_SELECT_SUB_MODE;
}


void TIMER_voiTimer0dSetPreloadValue (u8 Copy_PreloadValue)
{
    TCNT0 = Copy_PreloadValue;
}

void TIMER_voidTimer0SetOCRValue (u8 Copy_COMPValue)
{
    OCR0 = Copy_COMPValue;
}

void TIMER_voidTimer0EnableInterrupt(u8 Copy_u8Mode)
{
    switch (Copy_u8Mode)
    {
    case OVF_MODE:
        SET_BIT(TIMSK, TIMSK_TOIE0);
        break;
    case CTC_MODE:
        SET_BIT(TIMSK, TIMSK_OCIE0);
        break;
    default:
        break;
    } 
}

void TIMER_voidTimer0DisableInterrupt(u8 Copy_u8Mode)
{
    switch (Copy_u8Mode)
    {
    case OVF_MODE:
        CLR_BIT(TIMSK, TIMSK_TOIE0);
        break;
    case CTC_MODE:
        CLR_BIT(TIMSK, TIMSK_OCIE0);
        break;
    default:
        break;
    } 
}


static void (* TIMER0_OVFNotification)(void) = NULL_POINTER;

void TIMER_voidTimer0SetOVFCallBack (void (* pvNotificationFunction)(void))
{
    TIMER0_OVFNotification = pvNotificationFunction;
}

static void (* TIMER0_COMPNotification)(void) = NULL_POINTER;

void TIMER_voidTimer0SetCOMPFCallBack (void (* pvNotificationFunction)(void))
{
    TIMER0_COMPNotification = pvNotificationFunction;
}


void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
    if(TIMER0_COMPNotification != NULL_POINTER)
    {
        TIMER0_COMPNotification();
    }
    else
    {
        //Do Noting
    }
}

void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
    if(TIMER0_OVFNotification != NULL_POINTER)
    {
        TIMER0_OVFNotification();
    }
    else
    {
        //Do Noting
    }
}

/**********************************************************************************************************/

/**********************************************TIMER_1*****************************************************/

void TIMER_voidTimer1Init(void)
{
    TCCR1B &= TIMER_PRESCALER_MASK_CLR;
    TCCR1B |= TIMER_COUNTER_PRESCALER_SELECT;

    TCCR1A &= TIMER1_SELECT_MODE_MASK_CLR_A;
    TCCR1A |= TIMER1_SELECT_MODE_A;

    TCCR1B &= TIMER1_SELECT_MODE_MASK_CLR_B;
    TCCR1B |= TIMER1_SELECT_MODE_B;

    #if(OC1A_CHANNEL == ENABLE)

        TCCR1A &= TIMER1_SUB_MODE_MSK_CLR_A;
        TCCR1A |= TIMER1_SELECT_SUB_MODE_A;
        
    #elif (OC1A_CHANNEL == DISABLE)


    #endif

    #if (OC1B_CHANNEL == ENABLE)
        
        TCCR1A &= TIMER1_SUB_MODE_MSK_CLR_B;
        TCCR1A &= TIMER1_SELECT_SUB_MODE_B;
    
    #elif(OC1B_CHANNEL == DISABLE)

    #endif

}


void TIMER_voidTimer1SetPreloadValue(u16 Copy_u16PreloadValue)
{
    TCNT1 = Copy_u16PreloadValue;
}

void TIMER_voidTimer1SetOCRAMatchValue(u16 Copy_u16CompareMatchValue)
{
    OCR1A = Copy_u16CompareMatchValue;
}

void TIMER_voidTimer1SetOCRBMatchValue(u16 Copy_u16CompareMatchValue)
{
    OCR1B = Copy_u16CompareMatchValue;
}

void TIMER_voidSetTopValue(u16 Copy_u16TopValue)
{
    ICR1 = Copy_u16TopValue;
}


void TIMER_voidTimer1EnableInterrupt(u8 Copy_u8Mode)
{
    switch (Copy_u8Mode)
    {
    case OVF_MODE:
        SET_BIT(TIMSK, TIMSK_TOIE1);
        break;
    case OC1A_MODE:
        SET_BIT(TIMSK, TIMSK_OCIE1A);
        break;
    case OC1B_MODE:
        SET_BIT(TIMSK, TIMSK_OCIE1B);
        break;

    default:
        break;
    }
}

void TIMER_voidTimer1DisableInterrupt(u8 Copy_u8Mode)
{
    switch (Copy_u8Mode)
    {
    case OVF_MODE:
        CLR_BIT(TIMSK, TIMSK_TOIE1);
        break;
    case OC1A_MODE:
    	CLR_BIT(TIMSK, TIMSK_OCIE1A);
    	break;
    case OC1B_MODE:
        CLR_BIT(TIMSK, TIMSK_OCIE1B);
        break;

    default:
        break;
    } 
}

void ICU_voidSenceModetrigger(u8 Copy_u8Mode)
{
    switch(Copy_u8Mode)
    {
    case RISING_EDGE:
        SET_BIT(TCCR1B, TCCR1B_ICES1);
        break;
    case FALLING_EDGE:
        CLR_BIT(TCCR1B, TCCR1B_ICES1);
        break;

    default:
    	break;
    }
}

void ICU_voidControlInterrupt(u8 Copy_u8Mode)
{
    switch (Copy_u8Mode)
    {
    case ENABLE:
        SET_BIT(TIMSK, TIMSK_TICIE1);
        break;
    case DISABLE:
        CLR_BIT(TIMSK, TIMSK_TICIE1);
        break;

    default:
        break;
    }
}

static void (* TIMER1_OVFNotification)(void) = NULL_POINTER;

void TIMER_voidTimer1SetOVFCallBack (void (* pvNotificationFunction)(void))
{
    TIMER1_OVFNotification = pvNotificationFunction;
}

static void (* TIMER1_COMPANotification)(void) = NULL_POINTER;

void TIMER_voidTimer1SetCOMPACallBack (void (* pvNotificationFunction)(void))
{
    TIMER1_COMPANotification = pvNotificationFunction;
}

static void (* TIMER1_COMPBNotification)(void) = NULL_POINTER;

void TIMER_voidTimer1SetCOMPBCallBack (void (* pvNotificationFunction)(void))
{
    TIMER1_COMPBNotification = pvNotificationFunction;
}

static void (* ICU_Notification)(void) = NULL_POINTER;

void ICU_voidCallBack (void (*pvNotificationFunction)(void))
{
    ICU_Notification = pvNotificationFunction;
}

void __vector_6(void)  __attribute__ ((signal));
void __vector_6(void)
{
    if(ICU_Notification != NULL_POINTER)
    {
        ICU_Notification();
    }
    else
    {
        //Do Noting
    }
}

void __vector_7 (void) __attribute__((signal));
void __vector_7 (void)
{
    if(TIMER1_COMPANotification != NULL_POINTER)
    {
        TIMER1_COMPANotification();
    }
    else
    {
        //Do Noting
    }
}

void __vector_8 (void) __attribute__((signal));
void __vector_8 (void)
{
    if(TIMER1_COMPBNotification != NULL_POINTER)
    {
        TIMER1_COMPBNotification();
    }
    else
    {
        //Do Noting
    }
}

void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
    if(TIMER1_OVFNotification != NULL_POINTER)
    {
        TIMER1_OVFNotification();
    }
    else
    {
        //Do Noting
    }
}

u16 TIMER_GetValueTCNT1(void)
{
	return(TCNT1);
}

u16 TIMER_GetValueICR1(void)
{
	return(ICR1);
}

u8 TIMER0_voidGetTCNT0Value(void)
{
    return TCNT0;
}


void TIMER_voidSetBusyWait_COMPMode (u32 Copy_u32Timeout)
{
    /*TIMER 2*/

    /*Set CTC Mode*/
    TCCR2 &= TIMER0_SELECT_MODE_MASK_CLR;
    TCCR2 |= TIMER0_CTC_MODE_MSK;

    TCCR2 &= TIMER_PRESCALER_MASK_CLR;
    TCCR2 |= TIMER_PRESCALER_DIV_BY_64;

	OCR2 = 125;

    u8 Local_u8TCCR2OldValue = TCCR2;
    u8 Local_u8OCR2OldValue = OCR2;

    u32 Local_u32TicksToWait = 0;
    while(Local_u32TicksToWait <= Copy_u32Timeout)
    {
        while(GET_BIT(TIFR, TIFR_OCF2) == 0);
        SET_BIT(TIFR, TIFR_OCF2);
        Local_u32TicksToWait++;
    }

    TCCR2 = Local_u8TCCR2OldValue;
    OCR2 = Local_u8OCR2OldValue;
}









































































