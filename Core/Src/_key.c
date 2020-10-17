/*
 * key.c
 *
 *  Created on: Sep 26, 2020
 *      Author: felipe
 */

#include "main.h"
#include "_key.h"
#include "_delay.h"


void tecladoInit(){
	teclaEscape.nombreTecla = KEY_ESCAPE;
	teclaEscape.estadoTecla = STATE_UP;

	teclaEnter.nombreTecla 	= KEY_ENTER;
	teclaEnter.estadoTecla  = STATE_UP;

	teclaUp.nombreTecla 	= KEY_UP;
	teclaUp.estadoTecla     = STATE_UP;

	teclaDown.nombreTecla 	= KEY_DOWN;
	teclaDown.estadoTecla   = STATE_UP;

	delayInit( &fsmBottonTime, TIEMPO_TECLA );

	busyKeyboard = false;
}

void teclado( void ){
	/* Se atiende a cada una de las teclas */
	if( delayRead( &fsmBottonTime )){
		fsmButtonUpdate( ENTER_Pin, &teclaEnter );
		fsmButtonUpdate( ESCAPE_Pin, &teclaEscape );
		fsmButtonUpdate( UP_Pin, &teclaUp );
		fsmButtonUpdate( DOWN_Pin, &teclaDown );
	}
}

/* función de inicialización y error */
void fsmButtonInitError( sTecla_t *key_t ){
    key_t->estadoTecla = STATE_UP;
}

// FSM Update Sate Function
void fsmButtonUpdate( uint16_t tecla, sTecla_t *tec){

	switch( tec->estadoTecla ){

	case STATE_UP:
		/* CHECK TRANSITION CONDITIONS */
		if( !HAL_GPIO_ReadPin(GPIOA, tecla) ){
			tec->estadoTecla = STATE_FALLING;
			busyKeyboard = false;
		}
		break;

	case STATE_DOWN:
		/* CHECK TRANSITION CONDITIONS */
		if( HAL_GPIO_ReadPin(GPIOA, tecla) ){
			tec->estadoTecla  = STATE_RISING;
		}
		else{
			tec->estadoTecla  = STATE_HOLD;
		}
		break;

	case STATE_FALLING:
		/* CHECK TRANSITION CONDITIONS */
		if( !HAL_GPIO_ReadPin(GPIOA, tecla) ){
			tec->estadoTecla = STATE_DOWN;
			//busyKeyboard = true;
		} else{
			tec->estadoTecla  = STATE_RISING;
		}
		break;

	case STATE_RISING:
		/* CHECK TRANSITION CONDITIONS */
		if( HAL_GPIO_ReadPin(GPIOA, tecla) ){
			tec->estadoTecla = STATE_UP;
			//busyKeyboard = false;
		} else{
			tec->estadoTecla  = STATE_FALLING;
		}
		break;

	case STATE_HOLD:
		/* CHECK TRANSITION CONDITIONS */
		if( HAL_GPIO_ReadPin(GPIOA, tecla) ){
			tec->estadoTecla = STATE_RISING;
		}
		break;

	default:
		fsmButtonInitError( tec );
		break;
   }
}


