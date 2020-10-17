/*
 * key.h
 *
 *  Created on: Sep 26, 2020
 *      Author: felipe
 */

#ifndef INC_KEY_H_
#define INC_KEY_H_

#include "_miBoolean.h"
#include "_delay.h"

#define TIEMPO_TECLA 40		// tiempo transcurrido entre muestras de las teclas

delay_t fsmBottonTime;		// variable que acumula el tiempo entre muestras
bool_t busyKeyboard;

typedef enum{
            STATE_UP,
            STATE_FALLING,
            STATE_RISING,
			STATE_DOWN,
			STATE_HOLD
} fsmButtonState_t;

typedef enum{
			KEY_ESCAPE,
			KEY_ENTER,
			KEY_UP,
			KEY_DOWN
} tecla_t;

typedef struct {
			tecla_t nombreTecla;
			fsmButtonState_t estadoTecla;
}sTecla_t;

sTecla_t teclaEnter, teclaEscape, teclaUp, teclaDown;

void teclado( void );
void tecladoInit( void );
void fsmButtonUpdate( uint16_t, sTecla_t*);

#endif /* INC_KEY_H_ */
