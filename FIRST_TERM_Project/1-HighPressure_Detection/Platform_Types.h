/*
 * Platform_Types.h
 *
 *  Created on: 24 Jul 2024
 *      Author: Mostafa Mourad
 */




/* platform types of data type */


 #include <stdbool.h>
 #include <stdint.h>

#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

 #ifndef _Bool
 #define _Bool unsigned char
 #endif


 #define CPU_TYPE_8 			8
 #define CPU_TYPE_16 		    16
 #define CPU_TYPE_32 		    32

 #define HIGH			 	    1
 #define LOW			 		0

 #define SET_HIGH     			0x01
 #define SET_LOW      			0x00


 #define SET_ON       			0x01
 #define SET_OFF      			0x00


 #define E_OK         			(unsigned char)0x01
 #define E_NOT_OK        		(unsigned char)0x00

 #define ZERO_INIT 				0

 /*boolen is FALSE OR TRUE */
 /* FALSE=0*/
 /* TRUE=1*/

 typedef _Bool             Boolean;

 #ifndef False
 #define False		(boolean)false
 #endif
 #ifndef True
 #define True		(boolean)true
 #endif


 /* unsigned*/

 typedef unsigned char       uint8;
 typedef unsigned short      uint16;
 typedef unsigned int        uint32;
 typedef unsigned long long  uint64;

 /*signed*/

 typedef signed  char       sint8;
 typedef signed  short      sint16;
 typedef signed  int        sint32;
 typedef signed  long long  sint64;


 /*REAL NUMBER*/

 typedef float 		float32;
 typedef double 	float64;

 /*volatile types*/

 typedef volatile int8_t	 vint8_t;
 typedef volatile uint8_t 	 vuint8_t;
 typedef volatile int16_t 	 vint16_t;
 typedef volatile uint16_t	 vuint16_t;
 typedef volatile int32_t 	 vint32_t;
 typedef volatile uint32_t 	 vuint32_t;
 typedef volatile int64_t 	 vint64_t;
 typedef volatile uint64_t 	 vuint64_t;



#endif /* PLATFORM_TYPES_H_ */
