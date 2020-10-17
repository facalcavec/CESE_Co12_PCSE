/*
 * miApp_Menu_ppal.c
 *
 *  Created on: Aug 19, 2020
 *      Author: felipe
 */

#include <_Menu.h>
#include "main.h"
#include "_key.h"
#include "stm32f1xx_hal.h"
#include "stm32_adafruit_lcd.h"



void menu( void ){

	if( pantalla == INICIAL )
		menuInit();

	if( pantalla == PRINCIPAL )
		menuPrincipal();

	if( pantalla == REPORTES )
		reportes();
}

/* Función que muestra el menú inicial */
void menuInit(){

	if( !staticScreen){
		staticScreen = true;
		menuCabecera( "CARGADOR DE BATERIAS");
		busyKeyboard = true;
	}

	if(sTime1.Seconds != comparaSegundos ){
		comparaSegundos = sTime1.Seconds;
		presentaHora( POSH_HORA, POSV_HORA, true);
	}

	if( sDate1.Date != comparaFecha ){
		comparaFecha = sDate1.Date;
		presentaFecha( POSH_FECHA, POSV_FECHA);
	}

	if (( teclaEnter.estadoTecla == STATE_DOWN ||
		  teclaDown.estadoTecla == STATE_DOWN ||
		  teclaUp.estadoTecla == STATE_DOWN ) &&
		  !busyKeyboard){

		pantalla = PRINCIPAL;
		staticScreen = false;
	}

	if ( teclaEscape.estadoTecla == STATE_DOWN && !busyKeyboard){

		generadorReportesAleatorios();
		busyKeyboard = true;
		staticScreen = false;
	}
}


/* Función que muestra el menú principal */
void menuPrincipal(){
	static uint8_t estadoMenu = MENU_PPAL1;
	bool_t refreshScreen = false;

	if( !staticScreen){
		staticScreen = true;
		menuCabecera( "MENU PRINCIPAL");
		refreshScreen = true;
		busyKeyboard = true;
	}

	if( busyKeyboard == false ){
		if( teclaEnter.estadoTecla == STATE_DOWN){
			staticScreen = false;
			switch( estadoMenu ){

			case MENU_PPAL1:
				pantalla = PAUSA;
				break;

			case MENU_PPAL2:
				pantalla = REPORTES;
				break;

			case MENU_PPAL3:
				pantalla = CONFIGURACION;
				break;

			default:
				break;
			}
		}

		if( teclaUp.estadoTecla == STATE_DOWN ){
			estadoMenu--;
			if( estadoMenu < INICIO_MENU_PRINCIPAL){
				estadoMenu = FIN_MENU_PRINCIPAL;
			}
		refreshScreen = true;
		}

		if( teclaDown.estadoTecla == STATE_DOWN ){
			estadoMenu++;
			if( estadoMenu > FIN_MENU_PRINCIPAL ){
				 estadoMenu = INICIO_MENU_PRINCIPAL;
			}
			refreshScreen = true;
		}

		if ( teclaEscape.estadoTecla == STATE_DOWN ){
				pantalla = INICIAL;
				staticScreen = false;
				comparaFecha = 0x040;
		}
	}

	if( refreshScreen ){
		BSP_LCD_SetFont(&Font24);

		if(estadoMenu == MENU_PPAL1){
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		}else{
			BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
		}
		BSP_LCD_DisplayStringAt(40, 100, "1. ARRANQUE MANUAL/PAUSA", LEFT_MODE);

		if(estadoMenu == MENU_PPAL2){
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		}else{
			BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
		}
		BSP_LCD_DisplayStringAt(40, 140, "2. REPORTES", LEFT_MODE);

		if(estadoMenu == MENU_PPAL3){
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		}else{
			BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
		}
		BSP_LCD_DisplayStringAt(40, 180, "3. CONFIGURACION", LEFT_MODE);

		refreshScreen = false;
		busyKeyboard = true;
	}
}

/* Función que muestra la cabecera del menú principal */
void menuCabecera( void* texto){

	BSP_LCD_Clear(LCD_COLOR_BLACK);

	BSP_LCD_SetFont(&Font24);
	BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
	BSP_LCD_DrawHLine(10,10, 460);
	BSP_LCD_DisplayStringAt(0, 25, texto, CENTER_MODE);
	BSP_LCD_DrawHLine(10,60, 460);
}

/* Función que muestra la hora */
void presentaHora( uint16_t posHh, uint16_t posVh, uint8_t segundos ){

	uint8_t hora[9];

	hora[0] = (sTime1.Hours / 16) + 48;
	hora[1] = (sTime1.Hours % 16) + 48;
	hora[2] = ':';
	hora[3] = (sTime1.Minutes / 16) + 48;
	hora[4] = (sTime1.Minutes % 16) + 48;
	hora[5] = 0;

	if( segundos == true ){
		hora[5] = ':';
		hora[6] = (sTime1.Seconds / 16) + 48;
		hora[7] = (sTime1.Seconds % 16) + 48;
		hora[8] = 0;
	}
	BSP_LCD_DisplayStringAt(posHh, posVh, hora, LEFT_MODE);
}

/* Función que muestra la fecha */
void presentaFecha( uint16_t posFh, uint16_t posFv){

	uint8_t fecha[9];

	fecha[0] = (sDate1.Date / 16) + 48;
	fecha[1] = (sDate1.Date % 16) + 48;
	fecha[2] = '/';
	fecha[3] = (sDate1.Month / 16) + 48;
	fecha[4] = (sDate1.Month % 16) + 48;
	fecha[5] = '/';
	fecha[6] = (sDate1.Year / 16) + 48;
	fecha[7] = (sDate1.Year % 16) + 48;
	fecha[8] = 0;

	BSP_LCD_DisplayStringAt(posFh, posFv, fecha, LEFT_MODE);
}

/*******************************************************************************************
 *
 * 		Solo para probar la grabacion de reportes en EEPROM
 *
 * *****************************************************************************************
 */
void generadorReportesAleatorios(){

	extern uint16_t lastReport;
	uint8_t pData[2];

	//eeprom_ReadBlock(  &hi2c1, EEPROM0, EEPROM_ADDRESS_REPORT, *pData, 2);
	while(HAL_I2C_Mem_Read( &hi2c1, EEPROM0, 1, I2C_MEMADD_SIZE_16BIT, pData, 2, 10)!= HAL_OK);

	lastReport = pData[0];
	lastReport = lastReport << 8;
	lastReport += pData[1];

	lastReport += 24;

	pData[1] = lastReport & 0x00ff;
	pData[0] = lastReport >> 8;

	//HAL_I2C_Mem_Write(&hi2c1, EEPROM0, EEPROM_ADDRESS_REPORT ,I2C_MEMADD_SIZE_16BIT, pData, 2, 100);
	eeprom_WriteBlock( &hi2c1, EEPROM0, EEPROM_ADDRESS_REPORT, pData, 2 );

	uint8_t pseudoMedicion[24];

	uint8_t delta = HAL_GetTick();

	delta = delta & 0x000000ff;

	pseudoMedicion[0] = sDate1.Date;
	pseudoMedicion[1] = sDate1.Month;
	pseudoMedicion[2] = sDate1.Year;

	pseudoMedicion[4] = 0x01;			//Ei
	pseudoMedicion[5] = 0xE0 + delta;

	pseudoMedicion[6] = 0x02;			//Eo
	pseudoMedicion[7] = 0x1E + delta;

	pseudoMedicion[8] = 0x04;			//Ii
	pseudoMedicion[9] = 0xA6 + delta;

	pseudoMedicion[10] = 0x00;			//Io
	pseudoMedicion[11] = 0x72 + delta;

	pseudoMedicion[12] = 0x00;			//Ti
	pseudoMedicion[13] = 0xDC + delta;

	pseudoMedicion[14] = 0x00;			//To
	pseudoMedicion[15] = 0xEC + delta;

	pseudoMedicion[16] = 0x03;			//fon
	pseudoMedicion[17] = 0x56 + delta;

	pseudoMedicion[18] = 0x04;			//abs
	pseudoMedicion[19] = 0x12 + delta;

	pseudoMedicion[20] = 0x03;			//Ti
	pseudoMedicion[21] = 0x7F + delta;

	eeprom_WriteBlock( &hi2c1, EEPROM0, lastReport, pseudoMedicion, 24 );

	comparaFecha = 0x50;

	//HAL_I2C_Mem_Write(&hi2c1, 0xA0, (uint16_t)lastReport, I2C_MEMADD_SIZE_16BIT, pseudoMedicion, 24, 100);

}




