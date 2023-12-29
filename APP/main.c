/*
 * main.c
 *
 *  Created on: Oct 31, 2023
 *      Author: Aziz
 */

#include "../LIB/STD_TYPES.h"

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/PORT/PORT_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"
#include "../MCAL/GIE/GIE_interface.h"

#include <util/delay.h>


Chain_t System;

void SystemFunc();
void Temp_Warning();
void Light_Warning();
void Voltage_Warning();

u16 Analog=0,Temp=0,Light=0,Voltage=0;

void main()
{
	PORT_voidInit();
	ADC_voidInit();

	EXTI_voidINT0Init();
	EXTI_voidINT1Init();
	EXTI_voidINT2Init();

	CLCD_voidInit();

	GIE_voidEnableGlobal();

	System.ChainChannels[0]=Channel0;
	System.ChainChannels[1]=Channel1;
	System.ChainChannels[2]=Channel2;
	System.ChainSize=3;
	System.ChainNotificatinFunc=&SystemFunc;
	EXTI_u8INTSetCallBack(&Temp_Warning,EXTI_INT0);
	EXTI_u8INTSetCallBack(&Light_Warning,EXTI_INT1);
	EXTI_u8INTSetCallBack(&Voltage_Warning,EXTI_INT2);

	while(1)
	{
		CLCD_voidGoToXY(0,0);
		CLCD_voidWriteString("Waiting");
		_delay_ms(2000);

		ADC_u8StartChainConversionAsync(&System);

		if(Temp>30)
		{
			DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN0,DIO_u8PIN_LOW);
		}
		if(Light>10)
		{
			DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN1,DIO_u8PIN_LOW);
		}
		if (Voltage>3)
		{
			DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8PIN_LOW);
		}
	}
}

void SystemFunc()
{
	Analog= ((u32)System.ChainResults[0]*5000UL)/(u32)1023;
	Temp=Analog/10;
	Analog= ((u32)System.ChainResults[1]*5000UL)/(u32)1023;
	Light=Analog/100;
	Analog= ((u32)System.ChainResults[2]*5000UL)/(u32)1023;
	Voltage=Analog/1000;
	CLCD_voidSendCommand(1);
	CLCD_voidGoToXY(0,0);
	CLCD_voidWriteString("Temp is ");
	ClCD_voidWriteInteger(Temp);
	_delay_ms(2000);
	CLCD_voidSendCommand(1);
	CLCD_voidGoToXY(0,0);
	CLCD_voidWriteString("Light is ");
	ClCD_voidWriteInteger(Light);
	_delay_ms(2000);
	CLCD_voidSendCommand(1);
	CLCD_voidGoToXY(0,0);
	CLCD_voidWriteString("Voltage is ");
	ClCD_voidWriteInteger(Voltage);
	_delay_ms(2000);
	CLCD_voidSendCommand(1);
}
void Temp_Warning()
{
	CLCD_voidSendCommand(1);
	CLCD_voidGoToXY(0,0);
	CLCD_voidWriteString("Warning Temp");
	_delay_ms(2000);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN0,DIO_u8PIN_HIGH);
}
void Light_Warning()
{
	CLCD_voidSendCommand(1);
	CLCD_voidGoToXY(0,0);
	CLCD_voidWriteString("High Light");
	_delay_ms(2000);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN1,DIO_u8PIN_HIGH);
}
void Voltage_Warning()
{
	CLCD_voidSendCommand(1);
	CLCD_voidGoToXY(0,0);
	CLCD_voidWriteString("High Voltage");
	_delay_ms(2000);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8PIN_HIGH);
}
