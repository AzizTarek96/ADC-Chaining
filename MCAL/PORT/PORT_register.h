/*****************************************************************/
/*****************************************************************/
/********************		Author: Amgad Samir		**************/
/********************		Layer: MCAL				**************/
/********************		SWC: PORT				**************/
/********************		Version: 1.00			**************/
/********************		Date: 31-8-2020			**************/
/*****************************************************************/
/*****************************************************************/

#ifndef PORT_REGISTER_H_
#define PORT_REGISTER_H_

#define PORTA		 *((volatile u8*)0x3B)
#define DDRA 		 *((volatile u8*)0x3A)

#define PORTB		 *((volatile u8*)0x38)
#define DDRB 		 *((volatile u8*)0x37)

#define PORTC		 *((volatile u8*)0x35)
#define DDRC 		 *((volatile u8*)0x34)

#define PORTD		 *((volatile u8*)0x32)
#define DDRD 		 *((volatile u8*)0x31)

#endif