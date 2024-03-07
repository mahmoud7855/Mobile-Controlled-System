#ifndef _ADC_INTERFACE_H
#define _ADC_INTERFACE_H


#define ADC_Channel_0        0b00000
#define ADC_Channel_1        0b00001
#define ADC_Channel_2        0b00010
#define ADC_Channel_3        0b00011
#define ADC_Channel_4        0b00100
#define ADC_Channel_5        0b00101
#define ADC_Channel_6        0b00110
#define ADC_Channel_7        0b00111


void ADC_voidInit(void);
u8 ACD_voidStartConversionSynchronous(u8 Copu_u8ADCChannel);
void ACD_voidStartConversionASynchronous(u8 Copu_u8ADCChannel, void(*NotificationFunction)(u8 *));
u8 ADC_voidMapping(u16 Copy_u8XMaxValue, u16 Copy_u8XMinValue, u8 Copy_u8YMaxValue, u8 Copy_u8YMinValue, u16 Copy_u8X);



#endif
