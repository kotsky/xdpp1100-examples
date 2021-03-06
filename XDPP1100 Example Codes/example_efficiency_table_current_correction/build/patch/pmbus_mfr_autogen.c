
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
** Created on:  2020-09-15
*/
/*lint -save -e960 */

#include <stdint.h>              /* uint*_t */
#include "fw_bool.h"             /* boolean type */
#include "pmbus_autogen.h"
#include "pmbus_mfr_autogen.h"




/* instantiate the command MFR_ESTIMATE_EFFICIENCY.
 */
PMBUS_CMD_t PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY;
uint8_t	PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY_DATA_LOOP0[1];  	// data array for command loop0
uint8_t	PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY_DATA_LOOP1[1];    // data array for command loop1 (pointer if common)
uint8_t	PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY_RANGE[2];  	// data array for range (common for loops)

/*
 * Initializes all of our pmbus structs that were generated by the script
 * Function gets called to setup command support array, initialize pointers to command data, and describe commands 
 */
void pmbus_mfr_autogen_init(void)
{


	/* initialize command structure for MFR_ESTIMATE_EFFICIENCY. */
	// MFR_ESTIMATE_EFFICIENCY COMMAND:
	//PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY.OPCODE = PMBUS_CMDCODE_MFR_ESTIMATE_EFFICIENCY;
	//PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY.WRITE_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_WRITE;
	//PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY.READ_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_READ;
	//PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY.NUM_BYTES = 1; // data only not including slave address and command
	//PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY.NUM_PROTOCOL_BYTES = 2;  // slave address command and any other non-data bytes
	//PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY.SUPPORTED = 1;
	//PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY.PROTECTED0 = 0;
	//PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY.PROTECTED1 = 0;
	//PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY.RANGE_TYPE = (uint8_t) PMBUS_RANGE_LINEAR11_UNSIGNED;
	PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY.RANGE = &PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY_RANGE[0];
	PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY_RANGE[0] = 0;
	PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY_RANGE[1] = 8;
	PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY.CMD_CONFIG = 0xc38123b1;
	PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY.DATA0 = &PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY.DATA1 = &PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY_DATA_LOOP1[0];  // set the pointer to the data array
	// RANGE SUPPORT for MFR_ESTIMATE_EFFICIENCY COMMAND:
	// now populate pointers to the supported commands for each page
	PMBUS_CMD_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ESTIMATE_EFFICIENCY] = &PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY;
	//PMBUS_CMD_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ESTIMATE_EFFICIENCY] = &PMBUS_CMD_MFR_ESTIMATE_EFFICIENCY;
	//lint -e{778} suppress "Constant expression evaluates to 0 in operation '&'" 
	PMBUS_CMD_SUPPORT_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ESTIMATE_EFFICIENCY/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ESTIMATE_EFFICIENCY&31u));
	//PMBUS_CMD_SUPPORT_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ESTIMATE_EFFICIENCY/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ESTIMATE_EFFICIENCY&31u));

}


