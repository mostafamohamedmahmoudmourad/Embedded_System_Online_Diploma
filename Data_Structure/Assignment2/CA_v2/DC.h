/*
 * DC.h
 *
 *  Created on: 7 Aug 2024
 *      Author: Mostafa Mourad
 */

#ifndef DC_H_
#define DC_H_

#include "state.h"
#include <stdlib.h>
enum{
	DC_idle,
	DC_busy
}DC_state_id;


//declare state functions DC.
STATE_define(DC_idle);
STATE_define(DC_busy);

void DC_init();
extern void (*DC_state)();

#endif /* DC_H_ */