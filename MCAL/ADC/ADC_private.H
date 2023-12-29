/*****************************************************************/
/*****************************************************************/
/***************		Author: Aziz Tarek		******************/
/***************		Layer: MCAL				******************/
/***************		SWC: ADC			    ******************/
/***************		Date: 31-10-2023		******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/


#ifndef		ADC_PRIVATE_H_
#define 	ADC_PRIVATE_H_

#define DIVIDE_BY_2 			0
#define DIVIDE_BY_2_5 			1
#define DIVIDE_BY_4 			2
#define DIVIDE_BY_8 			3
#define DIVIDE_BY_16 			4
#define DIVIDE_BY_32 			5
#define DIVIDE_BY_64 			6
#define DIVIDE_BY_128 			7

#define Left_Adjust				1
#define Right_Adjust			2

#define SINGLE_CONVERSION 		0
#define CHAIN_CONVERSION 		1


#define NORMAL_MODE				1
#define AUTO_TRIGGER_MODE		2


#define IDLE 					0
#define BUSY					1

#define ADC_PRESCALER_MASK		0b11111000

#define CHANNEL_MASK			0b11100000

#define MODE_MASK				0b00011111


#endif
