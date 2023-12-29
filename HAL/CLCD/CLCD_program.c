/*****************************************************************/
/*****************************************************************/
/***************		Author: Aziz Tarek		******************/
/***************		Layer: MCAL				******************/
/***************		SWC: DIO				******************/
/***************		Date: 25-7-2023			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#include"../../LIB/STD_TYPES.h"
#include<util/delay.h>

#include"../../MCAL/DIO/DIO_interface.h"
#include "CLCD_interface.h"
#include"CLCD_private.h"
#include"CLCD_config.h"



void CLCD_voidSendCommand (u8 Copy_u8Command)
{
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
}
void CLCD_voidSendData (u8 Copy_u8Data)
{
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
}
void CLCD_voidInit     (void)
{
	_delay_ms(40);

	CLCD_voidSendCommand (0b00111000);
	CLCD_voidSendCommand (0b00001100);
	CLCD_voidSendCommand (1);

}
void CLCD_voidGoToXY (u8 Copy_u8XPos , u8 Copy_u8YPos)
{
	u8 Local_u8DDRAMAddress;

	Local_u8DDRAMAddress=0x40*Copy_u8YPos+Copy_u8XPos;
	CLCD_voidSendCommand(Local_u8DDRAMAddress+(1<<7));

}
void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAddress,Local_u8Counter;

	Local_u8CGRAMAddress=Copy_u8PatternNumber *8;

	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);

	for(Local_u8Counter=0;Local_u8Counter<8;Local_u8Counter++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);
	}
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);
	CLCD_voidSendData(Copy_u8PatternNumber);

}




void CLCD_voidWriteString(u8* Local_u8String)
{
	u8 Local_u8Index = 0;
	while(Local_u8String[Local_u8Index] != '\0')
	{
		CLCD_voidSendData(Local_u8String[Local_u8Index]);
		Local_u8Index++;
	}
}

void ClCD_voidWriteInteger(u16 Local_u16Number)
{
	u16 Local_u16NumberArr[10]={0};
	u8 Local_u8Counter=0;
	if(Local_u16Number==0)
	{
		CLCD_voidSendData('0');
		return;
	}
	while(Local_u16Number != 0)
	{
		Local_u16NumberArr[Local_u8Counter]=Local_u16Number%10+'0';
		Local_u16Number=Local_u16Number/10;
		Local_u8Counter++;
	}
	while(Local_u8Counter !=0)
	{
		CLCD_voidSendData(Local_u16NumberArr[Local_u8Counter-1]);
		Local_u8Counter--;
	}

}
