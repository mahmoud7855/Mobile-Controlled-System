#include <avr/delay.h>

#include "../LIB/BIT_MATH.h"

#include "../LIB/Std_Types.h"

#include "../MCAL/UART/UART_interface.h"

#include "../MCAL/TIMER/TIMER_interface.h"

#include "../MCAL/DIO/DIO_interface.h"

#include "../MCAL/ADC/ADC_interface.h"

#include "../MCAL/EXTI/EXTI_interface.h"

#include "../MCAL/GIE/GIE_interface.h"



#include "../HAL/LCD/LCD_interface.h"

#include "../HAL/KPD/KPD_interface.h"

#include "../HAL/LM35/LM35_interface.h"

#include <string.h>

typedef struct LookDoor
{
	u8 UserName[20];
	u8 Password[20];

	struct StructPtr * ptr;
}Users;

Users Clints[7];

void Contacts (void);

void System (void);

int main (void)
{

	/* Initializations */
	UART_voidInit();

	TIMER_voidSetTopValue(20000);

	TIMER_voidTimer1SetOCRAMatchValue(450);

	TIMER_voidTimer1Init();

	LCD_voidInitPins();

	LCD_voidInit();

	ADC_voidInit();
	/*---------------------------------------------------------------------*/


/* Variables */
	u8 User[20];		// For Recieve Data From Blutooth module
	u8 Size = 0;		// For Hold The Size of Data Recieved
	u8 User_Flag = 0;	// Rise when the user name is correct
	u8 Pass_Flag = 0;	// Rise when the password is correct
	u8 Wrong_Flag = 0;	// Rise when the password is Wrong
	u8 Trys = 0;		// counts times of the wrong password
	u8 Check = 0;		// Hold the return of strncmp Function
	u8 LoopCounter = 0;	//used for loop the number of users
	/*---------------------------------------------------------------------*/

/*	 Pins Configration  */
	DIO_voidSetPinDirection(PORTD, PIN0, INPUT);	// RX PIN
	DIO_voidSetPinDirection(PORTD, PIN1, OUTPUT);	// TX PIN
	DIO_voidSetPinDirection(PORTD, PIN5, OUTPUT); 	// Servo Pin
	DIO_voidSetPinDirection(PORTA, PIN0, OUTPUT);	// Buzzer Pin
	DIO_voidSetPinDirection(PORTA, PIN1, OUTPUT);	// Led1 Pin
	DIO_voidSetPinDirection(PORTA, PIN2, OUTPUT);	// Led2 Pin
	DIO_voidSetPinValue(PORTA, PIN0, LOW);

	/*---------------------------------------------------------------------*/

	while(1)
	{
		/* Code */

		UART_voidTransmitSrting("\n\r");
		UART_voidTransmitSrting("\n\r");

		UART_voidTransmitSrting("Hello ");
		UART_voidTransmitSrting("\n\r");
		_delay_ms(1000);
		UART_voidTransmitSrting("Enter Your User Name: ");
		UART_voidTransmitSrting("\n\r");
		while(1)
		{
			Contacts();
			Size = UART_viodReceiveString(User);
			for(LoopCounter = 0; LoopCounter < 7; LoopCounter++)
			{
				Check = strncmp(User, Clints[LoopCounter].UserName, Size);
				if(Check == 13)
				{
					User_Flag = 1;
					Check = 0;
					break;
				}
			}

			if(User_Flag == 1)
			{
				User_Flag = 0;
				UART_voidTransmitSrting("Enter Your Pass");
				UART_voidTransmitSrting("\n\r");

				Size = UART_viodReceiveString(User);
				Check = strncmp(User, Clints[LoopCounter].Password, Size);
				while(Trys < 2)
				{
					if(Check == 13)
					{
						Pass_Flag = 1;
						Check = 0;
						if(LoopCounter == 0)
						{
							UART_voidTransmitSrting("Welcome Mahmoud");
							UART_voidTransmitSrting("\n\r");
							break;
						}
						else if(LoopCounter == 1)
						{
							UART_voidTransmitSrting("Welcome Omar");
							UART_voidTransmitSrting("\n\r");
							break;
						}
						else if(LoopCounter == 2)
						{
							UART_voidTransmitSrting("Welcome Peter");
							UART_voidTransmitSrting("\n\r");
							break;
						}
						else if(LoopCounter == 3)
						{
							UART_voidTransmitSrting("Welcome Karim");
							UART_voidTransmitSrting("\n\r");
							break;
						}
						else if(LoopCounter == 4)
						{
							UART_voidTransmitSrting("Welcome Abbas");
							UART_voidTransmitSrting("\n\r");
							break;
						}
						else if(LoopCounter == 5)
						{
							UART_voidTransmitSrting("Welcome ziad");
							UART_voidTransmitSrting("\n\r");
							break;
						}
						else if(LoopCounter == 6)
						{
							UART_voidTransmitSrting("Welcome Ragab");
							UART_voidTransmitSrting("\n\r");
							break;
						}

					}
					else
					{
						UART_voidTransmitSrting("Wrong Password, Please Try Again");
						UART_voidTransmitSrting("\n\r");
						Size = UART_viodReceiveString(User);
						Check = strncmp(User, Clints[LoopCounter].Password, Size);
						Trys++;
						if(Trys == 2)
						{
							UART_voidTransmitSrting("Max Limit");
							UART_voidTransmitSrting("\n\r");
							Wrong_Flag = 1;
							break;
						}
					}
				}
				if(Pass_Flag == 1 && Wrong_Flag == 0)
				{
					TIMER_voidTimer1SetOCRAMatchValue(1000);
					_delay_ms(2000);
					TIMER_voidTimer1SetOCRAMatchValue(2000);
					Pass_Flag = 0;
					System();
					break;
				}
				else if(Wrong_Flag == 1)
				{
					Trys = 0;
					while(1)
					{
						DIO_voidSetPinValue(PORTA, PIN0, HIGH);
					}
				}
			}
			else if(User_Flag == 0)
			{
				UART_voidTransmitSrting("You are not registered");
				break;
			}
		}
	}
}




void Contacts (void)
{
	strcpy(Clints[0].UserName, "Mahmoud");
	strcpy(Clints[0].Password, "152002");

	strcpy(Clints[1].UserName, "Omar");
	strcpy(Clints[1].Password, "52003");

	strcpy(Clints[2].UserName, "Peter");
	strcpy(Clints[2].Password, "122002");

	strcpy(Clints[3].UserName, "Karim");
	strcpy(Clints[3].Password, "52002");

	strcpy(Clints[4].UserName, "Abbas");
	strcpy(Clints[4].Password, "12002");

	strcpy(Clints[5].UserName, "ziad");
	strcpy(Clints[5].Password, "292003");

	strcpy(Clints[6].UserName, "Ragab");
	strcpy(Clints[6].Password, "252002");

}

void System (void)
{

	u8 Receiver = 0;
	UART_voidTransmitSrting("Press 1 To Open Led 1");
	UART_voidTransmitSrting("\n\r");
	UART_voidTransmitSrting("Press 2 To Open Led 2");
	UART_voidTransmitSrting("\n\r");
	while(1)
	{
		Receiver = UART_voidReceiveData();
		if(Receiver == '1')
		{
			DIO_voidSetPinValue(PORTA, PIN1, HIGH);
			DIO_voidSetPinValue(PORTA, PIN2, LOW);

		}
		else if(Receiver == '2')
		{
			DIO_voidSetPinValue(PORTA, PIN2, HIGH);
			DIO_voidSetPinValue(PORTA, PIN1, LOW);
		}
	}
}


