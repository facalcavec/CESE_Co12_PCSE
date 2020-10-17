/*
 * hex2Ascii.c
 *
 *  Created on: Oct 9, 2020
 *      Author: felipe
 */



//#include "hex2Ascii.h"
//#include "stm32_adafruit_lcd.h"
//#include "stm32f1xx_hal.h"
#include "_miBoolean.h"



void hex2Ascii( int32_t num, int8_t length, char filler, char* st )
{
	char buf[25];
	//char st[27];
	bool_t neg=false;
	int c=0, f=0;

	if (num==0)
	{
		if (length!=0)
		{
			for (c=0; c<(length-1); c++)
				st[c]=filler;
			st[c]=48;
			st[c+1]=0;
		}
		else
		{
			st[0]=48;
			st[1]=0;
		}
	}
	else
	{
		if (num<0)
		{
			neg=true;
			num=-num;
		}

		while (num>0)
		{
			buf[c]=48+(num % 10);
			c++;
			num=(num-(num % 10))/10;
		}
		buf[c]=0;

		if (neg)
		{
			st[0]=45;
		}

		if (length>(c+neg))
		{
			for (int i=0; i<(length-c-neg); i++)
			{
				st[i+neg]=filler;
				f++;
			}
		}

		for (int i=0; i<c; i++)
		{
			st[i+neg+f]=buf[c-i-1];
		}
		st[c+neg+f]=0;

	}
}



//void hex2Ascii( 	int16_t,
//					int16_t,
//					int32_t,
//					int8_t,
//					char,
//					int8_t,
//					int8_t,
//					char );
//
//void hex2Ascii( int16_t x, int16_t y, int32_t num, int8_t length, char filler, int8_t ancho, int8_t coma, char unidad )
//{
//	char buf[25];
//	char st[27];
//	bool_t neg=false;
//	int c=0, f=0;
//
//	if (num==0)
//	{
//		if (length!=0)
//		{
//			for (c=0; c<(length-1); c++)
//				st[c]=filler;
//			st[c]=48;
//			st[c+1]=0;
//		}
//		else
//		{
//			st[0]=48;
//			st[1]=0;
//		}
//	}
//	else
//	{
//		if (num<0)
//		{
//			neg=true;
//			num=-num;
//		}
//
//		while (num>0)
//		{
//			buf[c]=48+(num % 10);
//			c++;
//			num=(num-(num % 10))/10;
//		}
//		buf[c]=0;
//
//		if (neg)
//		{
//			st[0]=45;
//		}
//
//		if (length>(c+neg))
//		{
//			for (int i=0; i<(length-c-neg); i++)
//			{
//				st[i+neg]=filler;
//				f++;
//			}
//		}
//
//		for (int i=0; i<c; i++)
//		{
//			st[i+neg+f]=buf[c-i-1];
//		}
//		st[c+neg+f]=0;
//
//	}
//	if( ancho != 0 && unidad != 0 ){
//		uint8_t i = 0;
//		uint8_t j = 0;
//
//		for( i = 0; i < length; i++ ){
//			j++;
//			BSP_LCD_DisplayChar(( x + j * ancho ), y, st[i] );
//			if( i == 2 && coma == 1){
//				j++;
//				BSP_LCD_DisplayChar(( x + j * ancho ), y, '.' );
//			}
//		}
//		j++;
//		BSP_LCD_DisplayChar(( x + j * ancho ), y, unidad );
//	}
//	else{
//
//
//	}
//}




