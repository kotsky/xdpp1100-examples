
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

#include <stdint.h>              /* uint*_t */
#include "fw_bool.h"             /* boolean type */
#include "pmbus_autogen.h"
#include "pmbus_mfr_autogen.h"




/* instantiate the command MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.
 */
PMBUS_CMD_t PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST;
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST_DATA_LOOP0[2];  	// data array for command loop0
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST_DATA_LOOP1[2];    // data array for command loop1 (pointer if common)
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST_RANGE[2];  	// data array for range (common for loops)

/* instantiate the command MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.
 */
PMBUS_CMD_t PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1;
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1_DATA_LOOP0[2];  	// data array for command loop0
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1_DATA_LOOP1[2];    // data array for command loop1 (pointer if common)
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1_RANGE[2];  	// data array for range (common for loops)

/* instantiate the command MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.
 */
PMBUS_CMD_t PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2;
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2_DATA_LOOP0[2];  	// data array for command loop0
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2_DATA_LOOP1[2];    // data array for command loop1 (pointer if common)
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2_RANGE[2];  	// data array for range (common for loops)

/* instantiate the command MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.
 */
PMBUS_CMD_t PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3;
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3_DATA_LOOP0[2];  	// data array for command loop0
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3_DATA_LOOP1[2];    // data array for command loop1 (pointer if common)
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3_RANGE[2];  	// data array for range (common for loops)

/* instantiate the command MFR_ADAPTIVE_DEADTIMES_REGION_1.
 */
PMBUS_CMD_t PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1;
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1_DATA_LOOP0[24];  	// data array for command loop0
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1_DATA_LOOP1[24];    // data array for command loop1 (pointer if common)

/* instantiate the command MFR_ADAPTIVE_DEADTIMES_REGION_2.
 */
PMBUS_CMD_t PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2;
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2_DATA_LOOP0[24];  	// data array for command loop0
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2_DATA_LOOP1[24];    // data array for command loop1 (pointer if common)

/* instantiate the command MFR_ADAPTIVE_DEADTIMES_REGION_3.
 */
PMBUS_CMD_t PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3;
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3_DATA_LOOP0[24];  	// data array for command loop0
uint8_t	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3_DATA_LOOP1[24];    // data array for command loop1 (pointer if common)

/*
 * Initializes all of our pmbus structs that were generated by the script
 * Function gets called to setup command support array, initialize pointers to command data, and describe commands 
 */
void pmbus_mfr_autogen_init(void)
{


	/* initialize command structure for MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST. */
	// MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST COMMAND:
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.OPCODE = PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.WRITE_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_WRITE;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.READ_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_READ;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.NUM_BYTES = 2; // data only not including slave address and command
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.NUM_PROTOCOL_BYTES = 2;  // slave address command and any other non-data bytes
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.SUPPORTED = 1;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.PROTECTED0 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.PROTECTED1 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.RANGE_TYPE = (uint8_t) PMBUS_RANGE_LINEAR11_UNSIGNED;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.RANGE = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST_RANGE[0];
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST_RANGE[0] = 8;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST_RANGE[1] = 0;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.CMD_CONFIG = 0xc38223b1;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.DATA0 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST.DATA1 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST_DATA_LOOP1[0];  // set the pointer to the data array
	// RANGE SUPPORT for MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST COMMAND:
	// now populate pointers to the supported commands for each page
	PMBUS_CMD_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST;
	//PMBUS_CMD_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST;
	//lint -e{778} suppress "Constant expression evaluates to 0 in operation '&'" 
	PMBUS_CMD_SUPPORT_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST&31u));
	//PMBUS_CMD_SUPPORT_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST&31u));

	/* initialize command structure for MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1. */
	// MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1 COMMAND:
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.OPCODE = PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.WRITE_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_WRITE;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.READ_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_READ;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.NUM_BYTES = 2; // data only not including slave address and command
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.NUM_PROTOCOL_BYTES = 2;  // slave address command and any other non-data bytes
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.SUPPORTED = 1;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.PROTECTED0 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.PROTECTED1 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.RANGE_TYPE = (uint8_t) PMBUS_RANGE_LINEAR11_UNSIGNED;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.RANGE = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1_RANGE[0];
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1_RANGE[0] = 8;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1_RANGE[1] = 0;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.CMD_CONFIG = 0xc38223b2;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.DATA0 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1.DATA1 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1_DATA_LOOP1[0];  // set the pointer to the data array
	// RANGE SUPPORT for MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1 COMMAND:
	// now populate pointers to the supported commands for each page
	PMBUS_CMD_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1;
	//PMBUS_CMD_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1;
	//lint -e{778} suppress "Constant expression evaluates to 0 in operation '&'" 
	PMBUS_CMD_SUPPORT_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1&31u));
	//PMBUS_CMD_SUPPORT_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1&31u));

	/* initialize command structure for MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2. */
	// MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2 COMMAND:
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.OPCODE = PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.WRITE_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_WRITE;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.READ_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_READ;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.NUM_BYTES = 2; // data only not including slave address and command
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.NUM_PROTOCOL_BYTES = 2;  // slave address command and any other non-data bytes
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.SUPPORTED = 1;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.PROTECTED0 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.PROTECTED1 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.RANGE_TYPE = (uint8_t) PMBUS_RANGE_LINEAR11_UNSIGNED;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.RANGE = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2_RANGE[0];
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2_RANGE[0] = 8;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2_RANGE[1] = 0;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.CMD_CONFIG = 0xc38223b3;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.DATA0 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2.DATA1 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2_DATA_LOOP1[0];  // set the pointer to the data array
	// RANGE SUPPORT for MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2 COMMAND:
	// now populate pointers to the supported commands for each page
	PMBUS_CMD_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2;
	//PMBUS_CMD_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2;
	//lint -e{778} suppress "Constant expression evaluates to 0 in operation '&'" 
	PMBUS_CMD_SUPPORT_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2&31u));
	//PMBUS_CMD_SUPPORT_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2&31u));

	/* initialize command structure for MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3. */
	// MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3 COMMAND:
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.OPCODE = PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.WRITE_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_WRITE;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.READ_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_READ;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.NUM_BYTES = 2; // data only not including slave address and command
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.NUM_PROTOCOL_BYTES = 2;  // slave address command and any other non-data bytes
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.SUPPORTED = 1;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.PROTECTED0 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.PROTECTED1 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.RANGE_TYPE = (uint8_t) PMBUS_RANGE_LINEAR11_UNSIGNED;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.RANGE = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3_RANGE[0];
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3_RANGE[0] = 8;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3_RANGE[1] = 0;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.CMD_CONFIG = 0xc38223b4;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.DATA0 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3.DATA1 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3_DATA_LOOP1[0];  // set the pointer to the data array
	// RANGE SUPPORT for MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3 COMMAND:
	// now populate pointers to the supported commands for each page
	PMBUS_CMD_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3;
	//PMBUS_CMD_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3;
	//lint -e{778} suppress "Constant expression evaluates to 0 in operation '&'" 
	PMBUS_CMD_SUPPORT_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3&31u));
	//PMBUS_CMD_SUPPORT_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3&31u));

	/* initialize command structure for MFR_ADAPTIVE_DEADTIMES_REGION_1. */
	// MFR_ADAPTIVE_DEADTIMES_REGION_1 COMMAND:
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1.OPCODE = PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_1;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1.WRITE_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_BLOCK_WRITE;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1.READ_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_BLOCK_READ;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1.NUM_BYTES = 24; // data only not including slave address and command
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1.NUM_PROTOCOL_BYTES = 3;  // slave address command and any other non-data bytes
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1.SUPPORTED = 1;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1.PROTECTED0 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1.PROTECTED1 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1.RANGE_TYPE = (uint8_t) PMBUS_RANGE_ALL;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1.CMD_CONFIG = 0xc1d856b5;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1.DATA0 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1.DATA1 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1_DATA_LOOP1[0];  // set the pointer to the data array
	// RANGE SUPPORT for MFR_ADAPTIVE_DEADTIMES_REGION_1 COMMAND:
	// now populate pointers to the supported commands for each page
	PMBUS_CMD_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_1] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1;
	//PMBUS_CMD_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_1] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_1;
	//lint -e{778} suppress "Constant expression evaluates to 0 in operation '&'" 
	PMBUS_CMD_SUPPORT_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_1/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_1&31u));
	//PMBUS_CMD_SUPPORT_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_1/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_1&31u));

	/* initialize command structure for MFR_ADAPTIVE_DEADTIMES_REGION_2. */
	// MFR_ADAPTIVE_DEADTIMES_REGION_2 COMMAND:
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2.OPCODE = PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_2;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2.WRITE_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_BLOCK_WRITE;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2.READ_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_BLOCK_READ;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2.NUM_BYTES = 24; // data only not including slave address and command
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2.NUM_PROTOCOL_BYTES = 3;  // slave address command and any other non-data bytes
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2.SUPPORTED = 1;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2.PROTECTED0 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2.PROTECTED1 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2.RANGE_TYPE = (uint8_t) PMBUS_RANGE_ALL;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2.CMD_CONFIG = 0xc1d856b6;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2.DATA0 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2.DATA1 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2_DATA_LOOP1[0];  // set the pointer to the data array
	// RANGE SUPPORT for MFR_ADAPTIVE_DEADTIMES_REGION_2 COMMAND:
	// now populate pointers to the supported commands for each page
	PMBUS_CMD_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_2] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2;
	//PMBUS_CMD_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_2] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_2;
	//lint -e{778} suppress "Constant expression evaluates to 0 in operation '&'" 
	PMBUS_CMD_SUPPORT_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_2/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_2&31u));
	//PMBUS_CMD_SUPPORT_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_2/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_2&31u));

	/* initialize command structure for MFR_ADAPTIVE_DEADTIMES_REGION_3. */
	// MFR_ADAPTIVE_DEADTIMES_REGION_3 COMMAND:
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3.OPCODE = PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_3;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3.WRITE_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_BLOCK_WRITE;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3.READ_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_BLOCK_READ;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3.NUM_BYTES = 24; // data only not including slave address and command
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3.NUM_PROTOCOL_BYTES = 3;  // slave address command and any other non-data bytes
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3.SUPPORTED = 1;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3.PROTECTED0 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3.PROTECTED1 = 0;
	//PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3.RANGE_TYPE = (uint8_t) PMBUS_RANGE_ALL;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3.CMD_CONFIG = 0xc1d856b7;
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3.DATA0 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3.DATA1 = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3_DATA_LOOP1[0];  // set the pointer to the data array
	// RANGE SUPPORT for MFR_ADAPTIVE_DEADTIMES_REGION_3 COMMAND:
	// now populate pointers to the supported commands for each page
	PMBUS_CMD_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_3] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3;
	//PMBUS_CMD_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_3] = &PMBUS_CMD_MFR_ADAPTIVE_DEADTIMES_REGION_3;
	//lint -e{778} suppress "Constant expression evaluates to 0 in operation '&'" 
	PMBUS_CMD_SUPPORT_ARRAY_LOOP[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_3/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_3&31u));
	//PMBUS_CMD_SUPPORT_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_3/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_3&31u));

}


