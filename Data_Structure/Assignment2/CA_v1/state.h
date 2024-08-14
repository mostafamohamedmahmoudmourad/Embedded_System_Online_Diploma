/*
 * state.h
 *
 *  Created on: 7 Aug 2024
 *      Author: Mostafa Mourad
 */

#ifndef STATE_H_
#define STATE_H_

#define STATE_define(_statFUN_) 	void ST_##_statFUN_()
#define STATE(_statFUN_) 			ST_##_statFUN_

#endif /* STATE_H_ */