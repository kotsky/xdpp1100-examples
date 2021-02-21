/*
 * custom_vout_command_lut.h
/* ============================================================================
** Copyright (C) 2020 Infineon. All rights reserved.
**               Infineon Technologies, PSS SYS / DES
** ============================================================================
**
** ============================================================================
** This document contains proprietary information. Passing on and
** copying of this document, and communication of its contents is not
** permitted without prior written authorisation.
** ============================================================================
**
** Created on:  2020-11-20
*/

/* XADDR Usage: Custom VDAC Example Modification */

#ifndef SRC_USER_APP_CUSTOM_VOUT_COMMAND_LUT_H_
#define SRC_USER_APP_CUSTOM_VOUT_COMMAND_LUT_H_

#include "stdint.h"

/*
 * vout_target_lut is a Look-Up Table
 * to match measured resistance (res_meas)
 * with respective output voltage target
 * (vout_command).
 * Set your own resistance range (as res_set)
 * with own desired output voltage target
 */

#define VOUT_COMMAND_ROWS (4)

const uint16_t vout_command_lut[2][VOUT_COMMAND_ROWS] =
{
		{		// res_set LSB =  0.1172 kOhm
				75 ,  //  res_set0 = 8.8   kOhm max; count[ 1 ]
				133 , //  res_set1 = 15.6  kOhm max; count[ 2 ]
				286 , //  res_set2 = 33.5  kOhm max; count[ 3 ]
				616   //  res_set3 = 72.2  kOhm max; count[ 4 ]
				},{
				// vout_command LSB =  0.00390625
				0 ,   //  to be set 0.0 V if res_meas < res_set0; count[ 0 ]
				460 , //  to be set 1.8 V if res_meas < res_set1; count[ 1 ]
				640 , //  to be set 2.5 V if res_meas < res_set2; count[ 2 ]
				845 , //  to be set 3.3 V if res_meas < res_set3; count[ 3 ]
		}
};


#endif /* SRC_USER_APP_CUSTOM_VOUT_COMMAND_LUT_H_ */
