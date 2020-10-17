/*
 * miApp_Menu_ppal.h
 *
 *  Created on: Aug 19, 2020
 *      Author: felipe
 */

#ifndef INC__MENU_H_
#define INC__MENU_H_

#include "stm32f1xx_hal.h"
#include "_miBoolean.h"
#include "_eeprom.h"

#define POSH_HORA 				170
#define POSV_HORA 				190

#define POSH_FECHA				170
#define POSV_FECHA				150

#define INICIO_MENU_PRINCIPAL	1		//define el primer indice del menu principal
#define FIN_MENU_PRINCIPAL		3		//define el ultimo indice del menu principal

#define MENU_PPAL1 				1
#define MENU_PPAL2 				2
#define MENU_PPAL3 				3

#define INICIAL					0
#define PRINCIPAL				1
#define PAUSA					2
#define REPORTES				3
#define CONFIGURACION			4


extern RTC_TimeTypeDef sTime1;
extern RTC_DateTypeDef sDate1;

extern I2C_HandleTypeDef hi2c1;
extern RTC_HandleTypeDef hrtc;

//uint16_t dir = 0;
//char datoSend = 0;
//char datoRec = 0;

uint8_t staticScreen; 	//= false;
uint8_t pantalla;		// = INICIAL;

static uint8_t comparaSegundos;	// = 0x060;
static uint8_t comparaFecha;	// = 0x060;

void menu( void );
void menuCabecera( void* );
void menuPrincipal( void );
void menuInit(void);
void presentaHora( uint16_t, uint16_t, uint8_t);
void presentaFecha( uint16_t, uint16_t);
void reportes( void );

void generadorReportesAleatorios( void );

#endif /* INC__MENU_H_ */
