/*
 * reportes.h
 *
 *  Created on: Oct 9, 2020
 *      Author: felipe
 */

#ifndef INC_REPORTES_H_
#define INC_REPORTES_H_

#include <_Menu.h>
#include "main.h"
#include "_miBoolean.h"
#include "_key.h"
#include "_eeprom.h"

/* Definiciones privadas --------------------------------------------------------*/
#define ADD_CONT	1		// direccion del contador de reportes
#define SIZE_PACKET 	24		// tamano del paquete de datos
#define INI_ADD		32		// direccion donde comienza a guardrse los reportes
#define FILA1		100		// ubicacion de la primera fila de la presentacion
#define COLUMNA1	20		// ubicacion de la primera columna de la presentacion
#define COLUMNA2	260		// ubicacion de la segunda columna de la presentacion


/* Prototipos de las funciones --------------------------------------------------*/
void reportes( void );
void menuCabecera( void* );
void presentaParametro(int16_t, int16_t, char, char, char, int16_t, int8_t, int8_t);
//void hex2Ascii( int16_t, int16_t, int32_t, int8_t, char, int8_t, int8_t, char );
void hex2Ascii( int32_t, int8_t, char, char* );





#endif /* INC_REPORTES_H_ */
