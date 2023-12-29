/*****************************************************************/
/*****************************************************************/
/***************		Author: Aziz Tarek		******************/
/***************		Layer: 	MCAL			******************/
/***************		SWC: 	EXTI            ******************/
/***************		Date: 28-10-2023		******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/


#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"

#include"EXTI_interface.h"
#include"EXTI_config.h"
#include"EXTI_private.h"
#include"EXTI_register.h"

static void (*EXTI_pvINTCallBackFunc[3])(void)={NULL};

void EXTI_voidINT0Init(void)
{
#if EXTI_INT0_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);


#elif EXTI_INT0_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif EXTI_INT0_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#elif EXTI_INT0_SENSE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#else
#error "Wrong EXTI_INT0_SENSE configuration option"

#endif


#if EXTI_INT0_INTIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);

#elif EXTI_INT0_INTIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);

#else
#error "Wrong EXTI_INT0_INTIAL_STATE configuration option"

#endif
}
void EXTI_voidINT1Init(void)
{
#if EXTI_INT1_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);


#elif EXTI_INT1_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

#elif EXTI_INT1_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#elif EXTI_INT1_SENSE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#else
#error "Wrong EXTI_INT1_SENSE configuration option"

#endif


#if EXTI_INT1_INTIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);

#elif EXTI_INT1_INTIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);

#else
#error "Wrong EXTI_INT1_INTIAL_STATE configuration option"

#endif
}
void EXTI_voidINT2Init(void)
{
#if EXTI_INT2_SENSE == FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);

#elif EXTI_INT1_SENSE == RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);

#else
#error "Wrong EXTI_INT2_SENSE configuration option"

#endif


#if EXTI_INT2_INTIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);

#elif EXTI_INT2_INTIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT2);

#else
#error "Wrong EXTI_INT2_INTIAL_STATE configuration option"

#endif
}


u8 EXTI_u8SetSenseControl(u8 Copy_IntNumber , u8 Copy_u8Sense)
{
	u8 Local_ErrorState=OK;
	switch (Copy_IntNumber)
	{
	case	EXTI_INT0 :

		switch(Copy_u8Sense)
		{
		case LOW_LEVEL :	CLR_BIT(MCUCR,MCUCR_ISC00); CLR_BIT(MCUCR,MCUCR_ISC01); break;
		case ON_CHANGE :	SET_BIT(MCUCR,MCUCR_ISC00); CLR_BIT(MCUCR,MCUCR_ISC01); break;
		case FALLING_EDGE :	CLR_BIT(MCUCR,MCUCR_ISC00); SET_BIT(MCUCR,MCUCR_ISC01); break;
		case RISING_EDGE :	SET_BIT(MCUCR,MCUCR_ISC00); SET_BIT(MCUCR,MCUCR_ISC01); break;
		default:			Local_ErrorState=NOK;break;
		}

		break;

		case	EXTI_INT1 :

			switch(Copy_u8Sense)
			{
			case LOW_LEVEL :	CLR_BIT(MCUCR,MCUCR_ISC10); CLR_BIT(MCUCR,MCUCR_ISC11); break;
			case ON_CHANGE :	SET_BIT(MCUCR,MCUCR_ISC10); CLR_BIT(MCUCR,MCUCR_ISC11); break;
			case FALLING_EDGE :	CLR_BIT(MCUCR,MCUCR_ISC10); SET_BIT(MCUCR,MCUCR_ISC11); break;
			case RISING_EDGE :	SET_BIT(MCUCR,MCUCR_ISC10); SET_BIT(MCUCR,MCUCR_ISC11); break;
			default:			Local_ErrorState=NOK;break;
			}

			break;

			case	EXTI_INT2 :

				switch(Copy_u8Sense)
				{
				case RISING_EDGE :	SET_BIT(MCUCR,MCUCSR_ISC2); break;
				case FALLING_EDGE :	CLR_BIT(MCUCR,MCUCSR_ISC2); break;
				default:			Local_ErrorState=NOK;break;
				}

				break;

				default	: Local_ErrorState=NOK;
				break;
	}

	return Local_ErrorState ;
}
u8 EXTI_u8EnableInterrupt(u8 Copy_u8IntNumber)
{
	u8 Local_u8ErrorState=OK;
	switch(Copy_u8IntNumber)
	{
	case EXTI_INT0 : SET_BIT(GICR,GICR_INT0); break;
	case EXTI_INT1 : SET_BIT(GICR,GICR_INT1); break;
	case EXTI_INT2 : SET_BIT(GICR,GICR_INT2); break;
	default : Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
u8 EXTI_u8DisableInterrupt(u8 Copy_u8IntNumber)
{
	u8 Local_u8ErrorState=OK;
	switch(Copy_u8IntNumber)
	{
	case EXTI_INT0 : CLR_BIT(GICR,GICR_INT0); break;
	case EXTI_INT1 : CLR_BIT(GICR,GICR_INT1); break;
	case EXTI_INT2 : CLR_BIT(GICR,GICR_INT2); break;
	default : Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

u8 EXTI_u8INTSetCallBack(void (*Copy_pvCallBackFunc)(void),u8 Copy_u8IntNumber)
{
	u8 Local_u8ErrorState = OK;
	if(Copy_pvCallBackFunc != NULL)
	{
		EXTI_pvINTCallBackFunc[Copy_u8IntNumber]=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

void __vector_1 (void) __attribute__((signal));
void __vector_1(void)
{
	if(EXTI_pvINTCallBackFunc[EXTI_INT0] != NULL)
	{
		EXTI_pvINTCallBackFunc[EXTI_INT0]();
	}
	else
	{

	}
}
void __vector_2 (void) __attribute__((signal));
void __vector_2(void)
{
	if(EXTI_pvINTCallBackFunc[EXTI_INT1] != NULL)
	{
		EXTI_pvINTCallBackFunc[EXTI_INT1]();
	}
	else
	{

	}
}
void __vector_3 (void) __attribute__((signal));
void __vector_3(void)
{
	if(EXTI_pvINTCallBackFunc[EXTI_INT2] != NULL)
	{
		EXTI_pvINTCallBackFunc[EXTI_INT2]();
	}
	else
	{

	}
}
