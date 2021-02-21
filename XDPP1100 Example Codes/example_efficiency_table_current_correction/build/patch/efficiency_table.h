/*
** efficency_table.h
** ============================================================================
** Copyright (C) 2020 Infineon Technologies. All rights reserved.
**               Infineon Technologies, PSS
** ============================================================================
**
** ============================================================================
** This document contains proprietary information. Passing on and
** copying of this document, and communication of its contents is not
** permitted without prior written authorisation.
** ============================================================================
**
** Created on:  2020-01-10
*/

#ifndef SRC_USER_APP_EFFICIENCY_TABLE_H_
#define SRC_USER_APP_EFFICIENCY_TABLE_H_

#include <stdint.h>

/*	estimate_Efficiency
 * 	Efficiency Table
 *
 *	Vin\Pout	4W		8W		16W		32W		64W		80W
 * 	36Vdc		0.941	0.944	0.951	0.96	0.961	0.96
 *	48Vdc		0.941	0.945	0.952	0.963	0.964	0.958
 *	60Vdc		0.94	0.944	0.955	0.964	0.966	0.952
 *	75Vdc
 *
 *
 * Each element of efficiency table (as "eff") was recalculated accordingly following formula:
 * correction_element = 1 / eff - 1
 *
 *	New Table "correction_table" in u1.9 format <0.2% accuracy.
 *	[33, 30, 27, 21, 21],
 *	[33, 30, 26, 20, 19, 22],
 *	[33, 30, 24, 19, 18, 25],
 *	[36, 32, 26, 21, 18, 28]
 *
 * */

#define VIN_MAX_IDX 4
#define POUT_MAX_IDX 7


//
// Correction_table in u1.9 format. Is using for Input Current (Input Power) correction
const uint16_t correction_table [VIN_MAX_IDX][POUT_MAX_IDX] = {
		{0, 33, 30, 27, 21, 21},
		{0, 33, 30, 26, 20, 19, 22},
		{0, 33, 30, 24, 19, 18, 25},
		{0, 36, 32, 26, 21, 18, 28},
};
// Efficiency table U0.8 format. Is using for efficiency display via PMBus MFR_ESTIMATE_EFFICIENCY
const uint8_t efficiency_table [VIN_MAX_IDX][POUT_MAX_IDX] = {
		{0, 241, 242, 243, 246, 246, 246},
		{0, 241, 242, 244, 247, 247, 246},
		{0, 240, 242, 245, 247, 247, 244},
		{0, 239, 241, 244, 246, 247, 243},
};

const uint32_t 	Vin_table[VIN_MAX_IDX] 		= {36, 48, 60, 75};
const uint32_t 	Pout_table[POUT_MAX_IDX] 	= {0, 40, 80, 160, 320, 640, 800};


#endif /* SRC_USER_APP_EFFICIENCY_TABLE_H_ */
