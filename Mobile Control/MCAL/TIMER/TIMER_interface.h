#ifndef _TIMER_INTERFACE_H
#define _TIMER_INTERFACE_H

void TIMER_voidTimer0Init(void);

void TIMER_voidTimer1Init(void);

void TIMER_voidTimer0SetPreloadValue (u8 Copy_PreloadValue);

void TIMER_voidTimer0SetOCRValue (u8 Copy_COMPValue);

void TIMER_voidTimer1SetPreloadValue(u16 Copy_u16PreloadValue);

void TIMER_voidTimer1SetOCRAMatchValue(u16 Copy_u16CompareMatchValue);

void TIMER_voidTimer1SetOCRBMatchValue(u16 Copy_u16CompareMatchValue);

void TIMER_voidSetTopValue(u16 Copy_u16TopValue);

void ICU_voidSenceModetrigger(u8 Copy_u8Mode);

void TIMER_voidSetBusyWait_COMPMode(u32 Copy_u32Timeout);

void ICU_voidControlInterrupt(u8 Copy_u8Mode);

void TIMER_voidTimer1EnableInterrupt(u8 Copy_u8Mode);

void TIMER_voidTimer1DisableInterrupt(u8 Copy_u8Mode);

void TIMER_voidTimer0EnableInterrupt(u8 Copy_u8Mode);

void TIMER_voidTimer1DisableInterrupt(u8 Copy_u8Mode);

void TIMER_voidTimer0SetOVFCallBack (void (* Notification)(void));

void TIMER_voidTimer0SetCOMPFCallBack (void (* Notification)(void));

void ICU_voidCallBack (void (* Notification)(void));

void TIMER_voidTimer1SetCOMPACallBack (void (* Notification)(void));

void TIMER_voidTimer1SetCOMPBCallBack (void (* Notification)(void));

void TIMER_voidTimer1SetOVFCallBack (void (* Notification)(void));

u16 TIMER_GetValueICR1(void);

u16 TIMER_GetValueTCNT1(void);

u8 TIMER0_voidGetTCNT0Value(void);

#define OC1A_MODE       2
#define OC1B_MODE       3

#define OVF_MODE        0
#define CTC_MODE        1

#define ENABLE          0
#define DISABLE         1

#define RISING_EDGE     0
#define FALLING_EDGE    1



#endif
