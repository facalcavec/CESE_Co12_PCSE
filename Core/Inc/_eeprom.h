/*
 * eeprom.h
 *
 *  Created on: 11 oct. 2020
 *      Author: felipe
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "stm32f1xx_hal.h"
#include "main.h"
//#include "stm32f0xx_hal.h"
//#include "stm32f0xx_hal_i2c.h"

#define EEPROM0  0xA0							// direccion del chip de la EEPROM
#define	EEPROM_ADDRESS_INI_REPORTES 0x20		// direccion donde comienza los bloques de reportes
#define EEPROM_ADDRESS_REPORT 1					// direccion donde guarda la ultima posicion de memoria del reporte
#define MEM_SIZE 0x07FF							// tamano de la memoria 24LC256 -> 32K


uint8_t eeprom_WriteBlock(I2C_HandleTypeDef *hi2c, uint16_t devAddress, uint16_t memAddress, uint8_t *pData, uint16_t TxBufferSize);
uint8_t eeprom_ReadBlock(I2C_HandleTypeDef *hi2c, uint16_t devAddress, uint16_t memAddress, uint8_t *pData, uint16_t RxBufferSize);
uint8_t eeprom_EraseMemFull( I2C_HandleTypeDef *hi2c, uint16_t devAddress );
uint8_t eeprom_Init( I2C_HandleTypeDef *hi2c, uint16_t devAddress );

#endif /* INC_EEPROM_H_ */
