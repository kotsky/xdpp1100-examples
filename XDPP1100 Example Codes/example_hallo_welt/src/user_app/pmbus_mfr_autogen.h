
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
** Created on:  2020-09-14
*/
/*lint -save -e960 */


#ifndef PMBUS_MFR_AUTOGEN_H
#define PMBUS_MFR_AUTOGEN_H

#include <stdint.h>              /* uint*_t */
#include "fw_bool.h"             /* boolean type */
#include "pmbus_autogen.h"




#define PMBUS_CMDCODE_MFR_Hallo_Welt (0xB1)

/* instantiate the command MFR_Hallo_Welt.
 */
extern PMBUS_CMD_t PMBUS_CMD_MFR_Hallo_Welt;
extern uint8_t	PMBUS_CMD_MFR_Hallo_Welt_DATA_LOOP0[1];  	// data array for command loop0
extern uint8_t	PMBUS_CMD_MFR_Hallo_Welt_DATA_LOOP1[1];    // data array for command loop1 (pointer if common)


void pmbus_mfr_autogen_init(void);

// external handle functions
extern void PMBUS_HANDLE_MFR_Hallo_Welt(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction);

#endif   //#endif /* _PMBUS_MFR_AUTOGEN_H_ */


