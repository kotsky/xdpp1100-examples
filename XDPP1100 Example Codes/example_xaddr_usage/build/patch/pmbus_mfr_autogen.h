
/**
 * @file    ./src/user_app/pmbus_mfr_autogen.h
 * @brief   Automatically generated from output of pmbus compile script.
 */

/* ============================================================================
** Copyright (C) 2020 Infineon. All rights reserved.
**               Infineon Technologies, PMM SYS / DES
** ============================================================================
**
** ============================================================================
** This document contains proprietary information. Passing on and
** copying of this document, and communication of its contents is not
** permitted without prior written authorisation.
** ============================================================================
**
** Automatically generated by:  pmbus_xlsx2c.py shasta_pmbus.xlsx
** Created on:  2020-12-16
*/
/*lint -save -e960 */


#ifndef PMBUS_MFR_AUTOGEN_H
#define PMBUS_MFR_AUTOGEN_H

#include <stdint.h>              /* uint*_t */
#include "fw_bool.h"             /* boolean type */
#include "pmbus_autogen.h"




#define PMBUS_CMDCODE_MFR_VOUT_RES_MEAS (0xB1)

/* instantiate the command structure for MFR_VOUT_RES_MEAS.
 */
// instances of the struct one per command
extern PMBUS_CMD_t PMBUS_CMD_MFR_VOUT_RES_MEAS;
extern uint8_t	PMBUS_CMD_MFR_VOUT_RES_MEAS_DATA_LOOP0[2];  	// data array for command loop0
extern uint8_t	* PMBUS_CMD_MFR_VOUT_RES_MEAS_DATA_LOOP1;    // data array for command loop1 (pointer if common)


void pmbus_mfr_autogen_init(void);

// external handle functions

#endif   //#endif /* _PMBUS_MFR_AUTOGEN_H_ */


