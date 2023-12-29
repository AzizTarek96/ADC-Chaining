/*****************************************************************/
/*****************************************************************/
/***************		Author: Aziz Tarek		******************/
/***************		Layer: MCAL				******************/
/***************		SWC: DIO				******************/
/***************		Date: 25-7-2023			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendCommand (u8 Copy_u8Command);
void CLCD_voidSendData (u8 Copy_u8Data);
void CLCD_voidInit     (void);
void CLCD_voidGoToXY (u8 Copy_u8XPos , u8 Copy_u8YPos);
void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos);
void CLCD_voidWriteString(u8* Local_u8String);
void ClCD_voidWriteInteger(u16 Local_u16Number);


#endif
