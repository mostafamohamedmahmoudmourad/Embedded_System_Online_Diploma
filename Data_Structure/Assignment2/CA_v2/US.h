/*
 * US.h
 *
 *  Created on: 7 Aug 2024
 *      Author: Mostafa Mourad
 */

#ifndef US_H_
#define US_H_

#include "state.h"
#include <stdlib.h>
enum{
	US_busy
}US_state_id;


//declare state functions US.
STATE_define(US_busy);

void US_init();
extern void (*US_state)();


#endif /* US_H_ */
