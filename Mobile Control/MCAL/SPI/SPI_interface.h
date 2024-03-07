#ifndef _SPI_INTERFACE_H
#define _SPI_INTERFACE_H

void SPI_voidInit();
u8 SPI_voidTranceive (u8 Copy_u8Data);
void SPI_voidSetCallback (void (* Notification)(u8 *));

#endif