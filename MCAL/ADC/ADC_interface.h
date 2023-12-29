/*****************************************************************/
/*****************************************************************/
/***************		Author: Aziz Tarek		******************/
/***************		Layer: MCAL				******************/
/***************		SWC: ADC			    ******************/
/***************		Date: 31-10-2023		******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef		ADC_INTERFACE_H_
#define 	ADC_INTERFACE_H_

typedef struct
{
	u8  ChainChannels[8];
	u16 ChainResults[8];
	u8	 ChainSize;
	void (*ChainNotificatinFunc)(void);
}Chain_t;

void ADC_voidInit(void);

u8 ADC_u8StartSingleConversionSync(u8 Copy_u8Channel,u16* Copy_pu16Result);

u8 ADC_u8StartSingleConversionAsync(u8 Copy_u8Channel,u16* Copy_pu16Result,void(*Copy_pvVotificatinFunc)(void));

u8 ADC_u8StartChainConversionAsync(Chain_t * Copy_Chain);

void ADC_voidEnableInterrupt();
void ADC_voidDisableInterrupt();

#define Channel0	0
#define Channel1	1
#define Channel2	2
#define Channel3	3
#define Channel4	4
#define Channel5	5
#define Channel6	6
#define Channel7	7

#endif
