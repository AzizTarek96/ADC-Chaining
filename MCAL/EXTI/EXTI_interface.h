/*****************************************************************/
/*****************************************************************/
/***************		Author: Aziz Tarek		******************/
/***************		Layer: MCAL				******************/
/***************		SWC: EXTERNAL INTERRUPT ******************/
/***************		Date: 28-10-2023		******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


#define EXTI_INT0		0
#define EXTI_INT1		1
#define EXTI_INT2		2

#define LOW_LEVEL		1
#define ON_CHANGE		2
#define FALLING_EDGE	3
#define RISING_EDGE		4


void EXTI_voidINT0Init(void);
void EXTI_voidINT1Init(void);
void EXTI_voidINT2Init(void);

u8 EXTI_u8SetSenseControl(u8 Copy_IntNumber , u8 Copy_u8Sense);
u8 EXTI_u8EnableInterrupt(u8 Copy_u8IntNumber);
u8 EXTI_u8DisableInterrupt(u8 Copy_u8IntNumber);
u8 EXTI_u8INTSetCallBack(void (*Copy_pvCallBackFunc)(void),u8 Copy_u8IntNumber);


#endif
