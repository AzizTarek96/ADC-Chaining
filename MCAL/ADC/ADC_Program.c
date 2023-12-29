/*****************************************************************/
/*****************************************************************/
/***************		Author: Aziz Tarek		******************/
/***************		Layer: MCAL				******************/
/***************		SWC: ADC			    ******************/
/***************		Date: 31-10-2023		******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"

#include"ADC_register.h"
#include"ADC_interface.h"
#include"ADC_config.h"
#include"ADC_private.h"

static volatile u16* ADC_pu16ConversionResult= NULL ;

static volatile void (*ADC_pvNotificationFunc)(void)= NULL ;

static volatile u8* ADC_pu8ChainChannels = NULL ;

static volatile u8 ADC_u8ChainLength = 0 ;

static volatile u8 ADC_u8BusyState=IDLE;

static volatile u8 ADC_u8ISRSource;

static volatile u8 ADC_u8ChainIndex;

void ADC_voidInit()
{


	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#if ADC_DataResolution == Left_Adjust
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_DataResolution == Right_Adjust
	CLR_BIT(ADMUX,ADMUX_ADLAR);

#else
#error "Wrong ADC_DATAResolution configuration option"

#endif


#if ADC_MODE ==	NORMAL_MODE
	CLR_BIT(ADCSRA,ADCSRA_ADATE);

#elif ADC_MODE == AUTO_TRIGGER_MODE
	SET_BIT(ADCSRA,ADCSRA_ADATE);

	SFIOR &= MODE_MASK;
	SFIOR |= FREE_RUNNING_MODE;

#else
#error "Wrong ADC_MODE Configuration Option"

#endif

	ADCSRA&=ADC_PRESCALER_MASK;
	ADCSRA|=ADC_u8PRESCALER;

	SET_BIT(ADCSRA,ADCSRA_ADEN);
}
u8 ADC_u8StartSingleConversionSync(u8 Copy_u8Channel,u16* Copy_pu16Result)
{
	u8 Local_u8ErrorState=OK;

	u32 Local_u32Count=0;

	if(Copy_pu16Result != NULL)
	{
		if (ADC_u8BusyState==IDLE)
		{
			ADC_u8BusyState=BUSY;

			ADMUX&=CHANNEL_MASK;
			ADMUX|=Copy_u8Channel;
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			while((GET_BIT(ADCSRA,ADCSRA_ADIF))==0 )// && Local_u32Count < ADC_u32TIMEOUT)
			{
				Local_u32Count++;
			}

			//			if(Local_u32Count==ADC_u32TIMEOUT)
			//			{
			//				Local_u8ErrorState=TIMEOUT_STATE;
			//			}

			SET_BIT(ADCSRA,ADCSRA_ADIF);

#if ADC_DataResolution == Left_Adjust
			*Copy_pu16Result=ADCH;
#elif ADC_DataResolution == Right_Adjust
			*Copy_pu16Result=ADC;
#else
#error "Wrong ADC_DATAResolution configuration option"

#endif

			ADC_u8BusyState=IDLE;
		}
		else
		{
			Local_u8ErrorState=BUSY_STATE;
		}

	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}

u8 ADC_u8StartSingleConversionAsync(u8 Copy_u8Channel,u16* Copy_pu16Result,void(*Copy_pvVotificatinFunc)(void))
{
	u8 Local_u8ErrorState=OK;

	if((Copy_pu16Result != NULL) && (Copy_pvVotificatinFunc != NULL))
	{
		if (ADC_u8BusyState==IDLE)
		{
			ADC_u8BusyState=BUSY;

			ADC_u8ISRSource=SINGLE_CONVERSION;

			ADC_pu16ConversionResult = Copy_pu16Result;
			ADC_pvNotificationFunc = Copy_pvVotificatinFunc;

			ADMUX&=CHANNEL_MASK;
			ADMUX|=Copy_u8Channel;

			SET_BIT(ADCSRA,ADCSRA_ADIE);
			SET_BIT(ADCSRA,ADCSRA_ADSC);

		}
		else
		{
			Local_u8ErrorState=BUSY_STATE;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}


void ADC_voidStartConvAsyc(){
	ADMUX&=CHANNEL_MASK;
	ADMUX|=0;

//	SET_BIT(ADCSRA,ADCSRA_ADIE);
	SET_BIT(ADCSRA,ADCSRA_ADSC);
}
u8 ADC_u8StartChainConversionAsync(Chain_t * Copy_Chain)
{
	u8 Local_u8ErrorState=OK;

	if(Copy_Chain != NULL && (Copy_Chain-> ChainChannels != NULL) && (Copy_Chain-> ChainResults != NULL)
			&& (Copy_Chain-> ChainNotificatinFunc != NULL))
	{
		if(ADC_u8BusyState==IDLE)
		{
			ADC_u8BusyState=BUSY;

			ADC_u8ISRSource=CHAIN_CONVERSION;

			ADC_pu8ChainChannels = Copy_Chain-> ChainChannels;
			ADC_pu16ConversionResult = Copy_Chain -> ChainResults;
			ADC_u8ChainLength = Copy_Chain -> ChainSize;
			ADC_pvNotificationFunc = Copy_Chain -> ChainNotificatinFunc;

			ADC_u8ChainIndex = 0;

			ADMUX &= CHANNEL_MASK;
			ADMUX|= ADC_pu8ChainChannels[ADC_u8ChainIndex];

			SET_BIT(ADCSRA,ADCSRA_ADIE);
			SET_BIT(ADCSRA,ADCSRA_ADSC);

		}
		else
		{
			Local_u8ErrorState=BUSY_STATE;
		}

	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}

void ADC_voidEnableInterrupt()
{
	SET_BIT(ADCSRA,ADCSRA_ADIE);
}

void ADC_voidDisableInterrupt()
{
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
}

void __vector_16 (void)			__attribute__((signal));
void __vector_16 (void)
{

	if(ADC_u8ISRSource == SINGLE_CONVERSION)
	{
#if ADC_DataResolution == Left_Adjust
		*ADC_pu16ConversionResult=ADCH;
#elif ADC_DataResolution == Right_Adjust
		*ADC_pu16ConversionResult=ADC;
#else
#error "Wrong ADC_DATAResolution configuration option"

#endif


		ADC_u8BusyState = IDLE;

		 CLR_BIT(ADCSRA,ADCSRA_ADIE);

		if(ADC_pvNotificationFunc != NULL)
		{
			ADC_pvNotificationFunc();
		}

	}
	else
	{

#if ADC_DataResolution == Left_Adjust
		ADC_pu16ConversionResult[ADC_u8ChainIndex]=ADCH;
#elif ADC_DataResolution == Right_Adjust
		ADC_pu16ConversionResult[ADC_u8ChainIndex]=ADC;
#else
#error "Wrong ADC_DATAResolution configuration option"

#endif

		ADC_u8ChainIndex++;

		if(ADC_u8ChainIndex == ADC_u8ChainLength)
		{

			ADC_u8BusyState = IDLE;

			CLR_BIT(ADCSRA,ADCSRA_ADIE);


			if(ADC_pvNotificationFunc != NULL)
			{
				ADC_pvNotificationFunc();
			}
		}
		else
		{


			ADMUX &= CHANNEL_MASK;
			ADMUX|= ADC_pu8ChainChannels[ADC_u8ChainIndex];

			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
	}
}
