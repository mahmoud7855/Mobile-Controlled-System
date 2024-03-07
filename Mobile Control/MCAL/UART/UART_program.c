/*********************************************
 * Author:          Mahmoud G. Mahmoud
 * Creation Data:   15 DEC, 2023
 * Version:         v2.0
 * Compiler:        GNU GCC
 ********************************************/
/*********************************************
 * Version      Date                  Author                  Description
 * v2.0         15 DEC, 2023     Mahmoud G. Mahmoud       Add Receive Str Function 
 *********************************************/


#include "../../LIB/Std_Types.h"
#include "../../LIB/BIT_MATH.h"

#include "UART_config.h"
#include "UART_interface.h"
#include "UART_private.h"

void UART_voidInit()
{
    u8 Local_u8UCSRCTemp = 0;
    #if(TX_CIRCUIT == ENABLE)
        SET_BIT(UCSRB, UCSRB_TXEN);
    #elif(TX_CIRCUIT == DISABLE)
        CLR_BIT(UCSRB, UCSRB_TXEN);
    #endif

    #if(RX_CIRCUIT == ENABLE)
        SET_BIT(UCSRB, UCSRB_RXEN);
    #elif(RX_CIRCUIT == DISABLE)
        CLR_BIT(UCSRB, UCSRB_RXEN);
    #endif

    /*Caracter Size Select*/
    #if(UART_Character_SIZE == _5_BIT)
        SET_BIT(UBRRH, UBRRH_URSEL);
        CLR_BIT(Local_u8UCSRCTemp, UCSRA_UCSZ0);
        CLR_BIT(Local_u8UCSRCTemp, UCSRA_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);

    #elif(UART_Character_SIZE == _6_BIT)
        SET_BIT(UBRRH, UBRRH_URSEL);
        SET_BIT(Local_u8UCSRCTemp, UCSRA_UCSZ0);
        CLR_BIT(Local_u8UCSRCTemp, UCSRA_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);

    #elif(UART_Character_SIZE == _7_BIT)
        SET_BIT(UBRRH, UBRRH_URSEL);
        CLR_BIT(Local_u8UCSRCTemp, UCSRA_UCSZ0);
        SET_BIT(Local_u8UCSRCTemp, UCSRA_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);

    #elif(UART_Character_SIZE == _8_BIT)
        SET_BIT(UBRRH, UBRRH_URSEL);
        SET_BIT(Local_u8UCSRCTemp, UCSRC_UCSZ0);
        SET_BIT(Local_u8UCSRCTemp, UCSRC_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);

    #elif(UART_Character_SIZE == _9_BIT)
        SET_BIT(UBRRH, UBRRH_URSEL);
        SET_BIT(Local_u8UCSRCTemp, UCSRA_UCSZ0);
        SET_BIT(Local_u8UCSRCTemp, UCSRA_UCSZ1);
        SET_BIT(UCSRB, UCSRB_UCSZ2);
    #endif

    /*Parity Mode Select*/
    #if(PARITY_MODE == DISABLE)
        SET_BIT(Local_u8UCSRCTemp, UCSRC_URSEL);
        CLR_BIT(Local_u8UCSRCTemp, UCSRC_UPM0);
        CLR_BIT(Local_u8UCSRCTemp, UCSRC_UPM1);
    
    #elif(PARITY_MODE == ODD_PARITY)
        SET_BIT(Local_u8UCSRCTemp, UCSRC_URSEL);
        SET_BIT(Local_u8UCSRCTemp, UCSRC_UPM0);
        CLR_BIT(Local_u8UCSRCTemp, UCSRC_UPM1);

    #elif(PARITY_MODE == EVEN_PARITY)   
        SET_BIT(Local_u8UCSRCTemp, UCSRC_URSEL);
        CLR_BIT(Local_u8UCSRCTemp, UCSRC_UPM0);
        SET_BIT(Local_u8UCSRCTemp, UCSRC_UPM1);
    #endif

    /*Stop Bit Select*/
    #if(STOP_BIT_SELECT == _1_BIT)
        SET_BIT(Local_u8UCSRCTemp, UCSRC_URSEL);
        CLR_BIT(Local_u8UCSRCTemp, UCSRC_USBS);
    #elif(STOP_BIT_SELECT == _2_BIT)
        SET_BIT(Local_u8UCSRCTemp, UCSRC_URSEL);
        SET_BIT(Local_u8UCSRCTemp, UCSRC_USBS);
    #endif
    /*USART Mode Select*/
    #if(USART_MODE_SELECT == ASYNCHRONOUS)
        SET_BIT(Local_u8UCSRCTemp, UCSRC_URSEL);
        CLR_BIT(Local_u8UCSRCTemp, UCSRC_UMSEL);
    #elif(USART_MODE_SELECT == SYNCHRONOUS)
        SET_BIT(Local_u8UCSRCTemp, UCSRC_URSEL);
        SET_BIT(Local_u8UCSRCTemp, UCSRC_UMSEL);
    #endif

    /*Boud Rate Select*/
    #if(BOUD_RATE == BOUD_9600)
        CLR_BIT(UBRRH, UBRRH_URSEL);
        UBRRL = 51;
        UBRRH = 0;
    #elif(BOUD_RATE == BOUD_11520)
        CLE_BIT(UBRRH, UBRRH_URSEL);
        UBRRL = 3;
        UBRRH = 0;
    #endif

    /*Transmission Speed*/
    #if(TRANSMISSION_SPEED == DOUBLE_SPEED)
        SET_BIT(UCSRA, UCSRA_U2X);
    #elif(TRANSMISSION_SPEED == NO_DOUBLE_SPEED)
        CLR_BIT(UCSRA, UCSRA_U2X);
    #endif
    UCSRC = Local_u8UCSRCTemp;
}

u8 TransmitedData = 0;
void UART_voidTransmitData(u16 Copy_u8Data)
{
    while(GET_BIT(UCSRA, UCSRA_UDRE) == 0);
    UDR = Copy_u8Data;
    while (GET_BIT(UCSRA, UCSRA_TXC) == 0);
    SET_BIT(UCSRA, UCSRA_TXC);
}

u8 UART_voidReceiveData()
{
    while (GET_BIT(UCSRA, UCSRA_RXC) == 0);
    return (UDR);
}

void UART_voidTransmitNumber(u32 Copy_u32Number)
{
    u8 Local_u8SpllitedNumber[10];
    s8 Local_s8LoopCounter = 0;
    while (Copy_u32Number != 0)
    {
        Local_u8SpllitedNumber[Local_s8LoopCounter] = Copy_u32Number % 10;
        Copy_u32Number /= 10;
        Local_s8LoopCounter++;
    }
    Local_s8LoopCounter--;
    while (Local_s8LoopCounter >= 0)
    {
        UART_voidTransmitData(Local_u8SpllitedNumber[Local_s8LoopCounter] + '0');
        Local_s8LoopCounter--;
    }  
}

void UART_voidTransmitSrting(const u8 * Ref_pu8String)
{
	while(* Ref_pu8String)
    {
		UART_voidTransmitData(* Ref_pu8String);
		Ref_pu8String++;
	}
}

u16 UART_viodReceiveString(u8 * Ref_pu8String)
{
	u8 Data;
	u8 Length = 0;
	UDR = 0;
	do
	{
		Data = UART_voidReceiveData();
		if(Data != '\n')
		{
			Ref_pu8String[Length] = Data;
			Length++;
		}
		else
		{
			Data = NULL_TERMINATOR;
			break;
		}
	}while (GET_BIT(UCSRA, UCSRA_RXC) == 0);
	//UART_voidTransmitSrting(Ref_pu8String);
	return(Length);
}
void Clear_UDR(void)
{
	UDR = 0;
}



void(*UART_NotificationFunction)(u8 *) = NULL_POINTER;
void UART_voidReceiveDataASynchronous(void(*NotificationFunction)(u8 *))
{
    UART_NotificationFunction = NotificationFunction;
    SET_BIT(UCSRB, UCSRB_RXCIE);
}

u8 UART_u8Data = 0;
void vector_13 (void)   __attribute__((signal));
void vector_13 (void)
{
    if(UART_NotificationFunction != NULL_POINTER)
    {
            UART_u8Data = UDR;
            UART_NotificationFunction(&UART_u8Data);
    }
    else
    {
        
    }
}




