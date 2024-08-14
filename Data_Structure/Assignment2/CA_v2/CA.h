/*
 * CA.h
 *
 *  Created on: 7 Aug 2024
 *      Author: Mostafa Mourad
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"
#include <stdlib.h>
enum{
	CA_waiting,
	CA_driving
}CA_state_id;


//declare state functions CA.
STATE_define(CA_waiting);
STATE_define(CA_driving);


extern void (*CA_state)();

#endif /* CA_H_ */
