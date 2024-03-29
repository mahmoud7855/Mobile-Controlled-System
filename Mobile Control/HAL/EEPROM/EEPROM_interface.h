/*********************************************
 * Author:          Mahmoud G. Mahmoud
 * Creation Data:   19 DEC, 2023
 * Version:         v2.0
 * Compiler:        GNU GCC
 ********************************************/
/*********************************************
 * Version      Date                  Author                  Description
 * v2.0         19 DEC, 2023     Mahmoud G. Mahmoud       Add EEPROM_u8ReadDataByteSequance Function
 *********************************************/

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte);

u8 EEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress);

#endif
