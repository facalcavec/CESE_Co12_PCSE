/*
 * reportes.c
 *
 *  Created on: Oct 9, 2020
 *      Author: felipe
 */

#include "_eeprom.h"
#include "_reportes.h"
#include "stm32_adafruit_lcd.h"

void reportes(){

	bool_t screenReporterChange = false;
	uint8_t read_data[24];
	uint16_t add_navegacion = 0;
	static int16_t navAddress = 0;


	// Se presenta el título del menu una sola vez
	if( !staticScreen ){

		staticScreen = true;				// se setea este flag para no volver a escribir el encabezado
		menuCabecera( "REPORTES");
		busyKeyboard = true;				// este flag se limpia una vez que se soltó la tecla
		screenReporterChange = true;		// avisa que hay que refrescar la pantalla

		HAL_I2C_Mem_Read(&hi2c1, EEPROM0, EEPROM_ADDRESS_REPORT, 2, read_data, 2, 10 );

		lastReport = (uint16_t) read_data[0];			// se fucionan los bytes de dirección
		lastReport = (lastReport << 8 ) + read_data[1];
	}

	if( teclaEscape.estadoTecla == STATE_DOWN){

		pantalla = PRINCIPAL;				// con ESCAPE se vuelve al menú principal
		staticScreen = false;				// se habilita la escritura de la nueva pantalla
		busyKeyboard = true;				// este flag se limpia una vez que se soltó la tecla
	}

	if( !busyKeyboard ){
		if( teclaUp.estadoTecla == STATE_DOWN ){
			navAddress++;
			if( navAddress > 0 )
				navAddress = 0;
			screenReporterChange = true;
		}

		if( teclaDown.estadoTecla == STATE_DOWN ){
			navAddress--;
			if( navAddress <= ( EEPROM_ADDRESS_INI_REPORTES - lastReport )/SIZE_PACKET )
				navAddress = (EEPROM_ADDRESS_INI_REPORTES - lastReport )/SIZE_PACKET;

			screenReporterChange = true;
		}

		if( teclaEnter.estadoTecla == STATE_DOWN ){

			eeprom_EraseMemFull( &hi2c1, EEPROM0 );
			busyKeyboard = true;
		}

	}
	if( screenReporterChange ){

		busyKeyboard = true;

		read_data[1] = (uint8_t) ( navAddress & 0x00ff );
		read_data[0] = (uint8_t) navAddress >> 8;

		presentaParametro( 20, 80, 'N', 'r', ' ',  navAddress, 17, 0 );

		while( HAL_I2C_Mem_Read(&hi2c1, EEPROM0, EEPROM_ADDRESS_REPORT, 2, read_data, 2, 10 ) != HAL_OK);

		add_navegacion = read_data[0];
		add_navegacion = add_navegacion << 8;
		add_navegacion += read_data[1];

		add_navegacion += navAddress * SIZE_PACKET;

		while( HAL_I2C_Mem_Read( &hi2c1, EEPROM0, add_navegacion, I2C_MEMADD_SIZE_16BIT, read_data, 24, 10)!= HAL_OK);

		uint16_t vector[SIZE_PACKET/2];

		int i,j;

		for( i = 0; i < SIZE_PACKET/2; i++ ){

			j = 2 * i;
			vector[i] = ( uint16_t )read_data[j];
			vector[i] = ( vector[i] << 8 ) + (uint16_t)read_data[j+1];

		}


		presentaFecha( 260, 80);
		presentaParametro( 20, 120, 'E', 'i', 'V', vector[2], 17, 1 );
		presentaParametro( 260, 120, 'E', 'o', 'V', vector[3], 17, 1 );
		presentaParametro( 20, 160, 'I', 'i', 'A', vector[4], 17, 1 );
		presentaParametro( 260, 160, 'I', 'o', 'A', vector[5], 17, 1 );
		presentaParametro( 20, 200, 'T', 'i', 'C', vector[6],17, 1 );
		presentaParametro( 260, 200, 'T', 'o', 'C', vector[7], 17, 1 );
		BSP_LCD_DisplayStringAt(20, 240, "Fon", LEFT_MODE);
		presentaHora( 88, 240, false );
		BSP_LCD_DisplayStringAt(260, 240, "Abs", LEFT_MODE);
		presentaHora( 328, 240, false );
		BSP_LCD_DisplayStringAt(20, 280, "completa", LEFT_MODE);
		presentaParametro( 260, 280, 'A', 'H', ' ', vector[10], 17, 0 );
	}
}

void presentaParametro(
						int16_t x,
						int16_t y,
						char parametro,
						char sufijo,
						char unidad,
						int16_t valor,
						int8_t ancho,
						int8_t coma )
{

	BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
	BSP_LCD_DisplayChar( x, y, parametro );

	if( parametro != 'A' ){
		BSP_LCD_SetFont(&Font20);
		BSP_LCD_DisplayChar(( x + ancho), ( y + 4 ), sufijo );
	}
	else{
		BSP_LCD_DisplayChar(( x + ancho), y, sufijo );
	}
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayChar(( x + 2 * ancho), ( y + 5), '=' );

//	hex2Ascii(( x + 3 * ancho), y, valor, cantidadCifras, ' ', ancho, coma, unidad );

	char numEnAscii[27];

	hex2Ascii( valor, 4, ' ', numEnAscii );

	uint8_t i = 0;
	uint8_t j = 0;

	for( i = 0; i < 4; i++ ){
		j++;
		BSP_LCD_DisplayChar(( x + ( j + 3 ) * ancho ), y, numEnAscii[i] );
		if( i == 2 && coma == 1){
			j++;
			BSP_LCD_DisplayChar(( x + ( j + 3 )  * ancho ), y, '.' );
		}
	}
	j++;
	BSP_LCD_DisplayChar(( x +  ( j + 3 )  * ancho ), y, unidad );
}

