/*
 * eeprom.c
 *
 *  Created on: 8 oct. 2020
 *      Author: felipe
 *
 *      Driver creado para la materia PCSE y que se integra al
 *      trabajo para el proyecto final del CESE Co12
 *
 *
 */



#include "_eeprom.h"


/**
  * @brief               :  Escribe un vector de bytes en una dirección específica.
  * 						Como la escritura de EEPROM es bloqueante, lo realiza en paquetes de
  * 						4 bytes para no tener mucha latencia si ocurre un cambio de contexto.
  *
  * @param  hi2c         : 	Puntero a la estructura I2C_HandleTypeDef que contiene la
  * 						información de configuración del I2C especificado.
  * @param	devAddress   :  Especifica la dirección del chip a ser programado (EEPROM ADDRESS).
  * @param	memAddress   : 	Dirección interna de la memoria.
  * @param	pData	     : 	Puntero del buffer de datos.
  * @param  txBufferSize : 	Cantidad de bytes que se quiere escribir.
  * @retval
  */
uint8_t eeprom_WriteBlock(I2C_HandleTypeDef *hi2c1, uint16_t devAddress, uint16_t memAddress, uint8_t *pData, uint16_t txBufferSize){

	// Si la posición de memoria es mayor al tamaño de la memoria vuelve, a la posición inicial
	if( memAddress + txBufferSize > MEM_SIZE ){

		memAddress = EEPROM_ADDRESS_INI_REPORTES;		//saturación de las address de la EEPROM
		lastReport = EEPROM_ADDRESS_INI_REPORTES;
	}

	if( txBufferSize >= 4 ){

		while( (txBufferSize - 4) >= 0 ){

			//escribe bloques de 4 bytes
			while(HAL_I2C_Mem_Write(hi2c1, (uint16_t)devAddress, (uint16_t)memAddress, I2C_MEMADD_SIZE_16BIT, pData, (uint16_t)4, 100)!= HAL_OK);

			txBufferSize -= 4;
			pData += 4;
			memAddress += 4;
		}
	}

	if( txBufferSize > 0 )
	// Escribe los ultimos bytes
	while(HAL_I2C_Mem_Write( hi2c1, (uint16_t)devAddress, (uint16_t)memAddress, I2C_MEMADD_SIZE_16BIT, pData, (uint16_t)4 - txBufferSize, 100)!= HAL_OK);

	return 1;
}

/**
  * @brief               :  lee un vector de bytes en una dirección específica.
  * 						Como la lectura de EEPROM es bloqueante, lo realiza en paquetes de
  * 						4 bytes para no tener mucha latencia si ocurre un cambio de contexto.
  *
  * @param  hi2c         : 	Puntero a la estructura I2C_HandleTypeDef que contiene la
  * 						información de configuración del I2C especificado.
  * @param	devAddress   :  Especifica la dirección del chip a ser programado (EEPROM ADDRESS).
  * @param	memAddress   : 	Dirección interna de la memoria.
  * @param	pData	     : 	Puntero del buffer de datos.
  * @param  txBufferSize : 	Cantidad de bytes que se quiere recibir.
  * @retval
  */
uint8_t eeprom_ReadBlock( I2C_HandleTypeDef *hi2c1, uint16_t devAddress, uint16_t memAddress, uint8_t *pData, uint16_t rxBufferSize){

	// Si la posición de memoria es mayor al tamaño de la memoria vuelve, a la posición inicial
	if( memAddress + rxBufferSize > MEM_SIZE ){

		memAddress = EEPROM_ADDRESS_INI_REPORTES;
		lastReport = EEPROM_ADDRESS_INI_REPORTES;
	}

	if( rxBufferSize >= 4 ){

		while( (rxBufferSize - 4) >= 0 ){

			//recibe bloques de 4 bytes
			while(HAL_I2C_Mem_Read(hi2c1, (uint16_t)devAddress, (uint16_t)memAddress, I2C_MEMADD_SIZE_16BIT, pData, (uint16_t)4 - rxBufferSize, 10)!= HAL_OK);

			rxBufferSize -= 4;
			pData += 4;
			memAddress += 4;
		}
	}

	if( rxBufferSize > 0 )
	// recibe los ultimos 4 bytes
	while(HAL_I2C_Mem_Read( hi2c1, (uint16_t)devAddress, (uint16_t)memAddress, I2C_MEMADD_SIZE_16BIT, pData, (uint16_t)2, 10)!= HAL_OK);

	return 1;
}

/**
  * @brief               :  Inicializa la eeprom e indica donde ir a leer los reportes.
  *
  * @param  hi2c         : 	Puntero a la estructura I2C_HandleTypeDef que contiene la
  * 						información de configuración del I2C especificado.
  * @param	devAddress   :  Especifica la dirección del chip a ser programado (EEPROM ADDRESS).
  * @retval
  */
uint8_t eeprom_Init( I2C_HandleTypeDef *hi2c1, uint16_t devAddress  ){

uint8_t firtStar[2];

//HAL_I2C_Mem_Read(&hi2c1, EEPROM0, 0, 2, firtStar, 1, 100 );

while(HAL_I2C_Mem_Read( hi2c1, devAddress, 0, I2C_MEMADD_SIZE_16BIT, firtStar, 1, 10)!= HAL_OK);

	if( firtStar[0] != 0xA5 ){

		firtStar[0] = 0xA5;
		while(HAL_I2C_Mem_Write( hi2c1, devAddress, 0, I2C_MEMADD_SIZE_16BIT, firtStar, 1, 100 ) != HAL_OK);
		//HAL_I2C_Mem_Write(&hi2c1, EEPROM0, 0, I2C_MEMADD_SIZE_16BIT, firtStar[0], 1, 100);

		firtStar[0] = 0;
		firtStar[1] = EEPROM_ADDRESS_INI_REPORTES;
		while(HAL_I2C_Mem_Write( hi2c1, devAddress, EEPROM_ADDRESS_REPORT, I2C_MEMADD_SIZE_16BIT, firtStar, 2, 100 )!= HAL_OK);
		//HAL_I2C_Mem_Write(&hi2c1, EEPROM0, ADD_CONT, I2C_MEMADD_SIZE_16BIT, firtStar, 2, 100);
		HAL_Delay(10);
	}

	while(HAL_I2C_Mem_Read( hi2c1, (uint16_t)devAddress, (uint16_t)EEPROM_ADDRESS_INI_REPORTES, I2C_MEMADD_SIZE_16BIT, firtStar, 2, 10)!= HAL_OK);

	lastReport = firtStar[0];
	lastReport = lastReport << 8;
	lastReport += firtStar[1];

	return 1;
}

/**
  * @brief               :  Borra el contenido completo de la memoria.
  *
  * @param  hi2c         : 	Puntero a la estructura I2C_HandleTypeDef que contiene la
  * 						información de configuración del I2C especificado.
  * @param	devAddress   :  Especifica la dirección del chip a ser programado (EEPROM ADDRESS).
  * @retval
  */
uint8_t eeprom_EraseMemFull( I2C_HandleTypeDef *hi2c1, uint16_t devAddress ){

	uint8_t eraseBuf[32] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
							0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

	uint32_t i;
	for (i = 0 ; i < 1024 ; i=i+32){
		while(HAL_I2C_Mem_Write(hi2c1, (uint16_t)devAddress, (uint16_t)i, I2C_MEMADD_SIZE_16BIT, eraseBuf, (uint16_t)32, 1000)!= HAL_OK);

		int32_t aaaa = 0;
		aaaa++;

	}
	return 1;
}
