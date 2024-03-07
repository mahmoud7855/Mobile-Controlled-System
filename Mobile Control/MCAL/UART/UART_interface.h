#ifndef _UART_INTERFACE_H
#define _UART_INTERFACE_H

void UART_voidInit();
void UART_voidTransmitData(u16 Copy_u8Data);
u8 UART_voidReceiveData();
void UART_voidTransmitNumber(u32 Copy_u32Number);
void UART_voidTransmitSrting(const u8 * Ref_pu8String);
u16 UART_viodReceiveString(u8 * Ref_pu8String);
void Clear_UDR(void);
void UART_voidReceiveDataASynchronous(void(*NotificationFunction)(u8 *));


#endif
