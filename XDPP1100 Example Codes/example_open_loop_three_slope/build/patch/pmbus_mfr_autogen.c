
/**
 * @file    ./src/user_app/pmbus_mfr_autogen.h
 * @brief   Automatically generated from output of pmbus compile script.
 */

/* ============================================================================
** Copyright (C) 2021 Infineon. All rights reserved.
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
** Created on:  2021-02-06
*/
/*lint -save -e960 */

#include <stdint.h>              /* uint*_t */
#include "fw_bool.h"             /* boolean type */
#include "pmbus_autogen.h"
#include "pmbus_mfr_autogen.h"




/* instantiate the command structure for MFR_SOFTSTART_IRQ_RATE_SEL.
 */
// instances of the struct one per command
PMBUS_CMD_t PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL;
uint8_t	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_DATA_LOOP0[1];  	// data array for command loop0
/*lint -esym(552,PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_DATA_LOOP1) */
/*lint -esym(844,PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_DATA_LOOP1) */
uint8_t	* PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_DATA_LOOP1;    // data array for command loop1 (pointer if common)
uint8_t	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_RANGE[9];  	// data array for range (common for loops)

/* instantiate the command structure for MFR_SOFTSTART_PWM_STEPSIZE.
 */
// instances of the struct one per command
PMBUS_CMD_t PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE;
uint8_t	PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE_DATA_LOOP0[4];  	// data array for command loop0
/*lint -esym(552,PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE_DATA_LOOP1) */
/*lint -esym(844,PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE_DATA_LOOP1) */
uint8_t	* PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE_DATA_LOOP1;    // data array for command loop1 (pointer if common)

/* instantiate the command structure for MFR_SOFTSTART_CYCLE_COUNT.
 */
// instances of the struct one per command
PMBUS_CMD_t PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT;
uint8_t	PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT_DATA_LOOP0[4];  	// data array for command loop0
/*lint -esym(552,PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT_DATA_LOOP1) */
/*lint -esym(844,PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT_DATA_LOOP1) */
uint8_t	* PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT_DATA_LOOP1;    // data array for command loop1 (pointer if common)

/* instantiate the command structure for MFR_SOFTSTART_MAX_FREQUENCY.
 */
// instances of the struct one per command
PMBUS_CMD_t PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY;
uint8_t	PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY_DATA_LOOP0[2];  	// data array for command loop0
/*lint -esym(552,PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY_DATA_LOOP1) */
/*lint -esym(844,PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY_DATA_LOOP1) */
uint8_t	* PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY_DATA_LOOP1;    // data array for command loop1 (pointer if common)

/*
 * Initializes all of our pmbus structs that were generated by the script
 * Function gets called to setup command support array, initialize pointers to command data, and describe commands 
 */
void pmbus_mfr_autogen_init(void)
{


	/* initialize command structure for MFR_SOFTSTART_IRQ_RATE_SEL. */
	// MFR_SOFTSTART_IRQ_RATE_SEL COMMAND:
	ptr_pmbus_callback[PMBUS_CMDCODE_MFR_SOFTSTART_IRQ_RATE_SEL] = PMBUS_HANDLE_MFR_SOFTSTART_IRQ_RATE_SEL;
	//PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL.OPCODE = PMBUS_CMDCODE_MFR_SOFTSTART_IRQ_RATE_SEL;
	//PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL.WRITE_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_WRITE;
	//PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL.READ_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_READ;
	//PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL.NUM_BYTES = 1; // data only not including slave address and command
	//PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL.NUM_PROTOCOL_BYTES = 2;  // slave address command and any other non-data bytes
	//PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL.SUPPORTED = 1;
	//PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL.PROTECTED0 = 0;
	//PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL.PROTECTED1 = 0;
	//PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL.RANGE_TYPE = (uint8_t) PMBUS_RANGE_SPARSE8;
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL.RANGE = &PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_RANGE[0];
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_RANGE[0] = 8;
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_RANGE[1] = 0x00;
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_RANGE[2] =  0x01;
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_RANGE[3] =  0x02;
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_RANGE[4] =  0x03;
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_RANGE[5] =  0x04;
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_RANGE[6] =  0x05;
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_RANGE[7] =  0x06;
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_RANGE[8] =  0x07;
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL.CMD_CONFIG = 0xc78123b1;
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL.DATA0 = &PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL.DATA1 = &PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_DATA_LOOP1 = &PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL_DATA_LOOP0[0];
	// RANGE SUPPORT for MFR_SOFTSTART_IRQ_RATE_SEL COMMAND:
	// now populate pointers to the supported commands for each page
	PMBUS_CMD_ARRAY_LOOP[PMBUS_CMDCODE_MFR_SOFTSTART_IRQ_RATE_SEL] = &PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL;
	//PMBUS_CMD_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_SOFTSTART_IRQ_RATE_SEL] = &PMBUS_CMD_MFR_SOFTSTART_IRQ_RATE_SEL;
	//lint -e{778} suppress "Constant expression evaluates to 0 in operation '&'" 
	PMBUS_CMD_SUPPORT_ARRAY_LOOP[PMBUS_CMDCODE_MFR_SOFTSTART_IRQ_RATE_SEL/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_SOFTSTART_IRQ_RATE_SEL&31u));
	//PMBUS_CMD_SUPPORT_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_SOFTSTART_IRQ_RATE_SEL/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_SOFTSTART_IRQ_RATE_SEL&31u));

	/* initialize command structure for MFR_SOFTSTART_PWM_STEPSIZE. */
	// MFR_SOFTSTART_PWM_STEPSIZE COMMAND:
	ptr_pmbus_callback[PMBUS_CMDCODE_MFR_SOFTSTART_PWM_STEPSIZE] = PMBUS_HANDLE_MFR_SOFTSTART_PWM_STEPSIZE;
	//PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE.OPCODE = PMBUS_CMDCODE_MFR_SOFTSTART_PWM_STEPSIZE;
	//PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE.WRITE_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_BLOCK_WRITE;
	//PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE.READ_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_BLOCK_READ;
	//PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE.NUM_BYTES = 4; // data only not including slave address and command
	//PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE.NUM_PROTOCOL_BYTES = 3;  // slave address command and any other non-data bytes
	//PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE.SUPPORTED = 1;
	//PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE.PROTECTED0 = 0;
	//PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE.PROTECTED1 = 0;
	//PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE.RANGE_TYPE = (uint8_t) PMBUS_RANGE_ALL;
	PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE.CMD_CONFIG = 0xc1c456b2;
	PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE.DATA0 = &PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE.DATA1 = &PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE_DATA_LOOP1 = &PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE_DATA_LOOP0[0];
	// RANGE SUPPORT for MFR_SOFTSTART_PWM_STEPSIZE COMMAND:
	// now populate pointers to the supported commands for each page
	PMBUS_CMD_ARRAY_LOOP[PMBUS_CMDCODE_MFR_SOFTSTART_PWM_STEPSIZE] = &PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE;
	//PMBUS_CMD_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_SOFTSTART_PWM_STEPSIZE] = &PMBUS_CMD_MFR_SOFTSTART_PWM_STEPSIZE;
	//lint -e{778} suppress "Constant expression evaluates to 0 in operation '&'" 
	PMBUS_CMD_SUPPORT_ARRAY_LOOP[PMBUS_CMDCODE_MFR_SOFTSTART_PWM_STEPSIZE/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_SOFTSTART_PWM_STEPSIZE&31u));
	//PMBUS_CMD_SUPPORT_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_SOFTSTART_PWM_STEPSIZE/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_SOFTSTART_PWM_STEPSIZE&31u));

	/* initialize command structure for MFR_SOFTSTART_CYCLE_COUNT. */
	// MFR_SOFTSTART_CYCLE_COUNT COMMAND:
	ptr_pmbus_callback[PMBUS_CMDCODE_MFR_SOFTSTART_CYCLE_COUNT] = PMBUS_HANDLE_MFR_SOFTSTART_CYCLE_COUNT;
	//PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT.OPCODE = PMBUS_CMDCODE_MFR_SOFTSTART_CYCLE_COUNT;
	//PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT.WRITE_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_BLOCK_WRITE;
	//PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT.READ_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_BLOCK_READ;
	//PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT.NUM_BYTES = 4; // data only not including slave address and command
	//PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT.NUM_PROTOCOL_BYTES = 3;  // slave address command and any other non-data bytes
	//PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT.SUPPORTED = 1;
	//PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT.PROTECTED0 = 0;
	//PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT.PROTECTED1 = 0;
	//PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT.RANGE_TYPE = (uint8_t) PMBUS_RANGE_ALL;
	PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT.CMD_CONFIG = 0xc1c456b3;
	PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT.DATA0 = &PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT.DATA1 = &PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT_DATA_LOOP1 = &PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT_DATA_LOOP0[0];
	// RANGE SUPPORT for MFR_SOFTSTART_CYCLE_COUNT COMMAND:
	// now populate pointers to the supported commands for each page
	PMBUS_CMD_ARRAY_LOOP[PMBUS_CMDCODE_MFR_SOFTSTART_CYCLE_COUNT] = &PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT;
	//PMBUS_CMD_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_SOFTSTART_CYCLE_COUNT] = &PMBUS_CMD_MFR_SOFTSTART_CYCLE_COUNT;
	//lint -e{778} suppress "Constant expression evaluates to 0 in operation '&'" 
	PMBUS_CMD_SUPPORT_ARRAY_LOOP[PMBUS_CMDCODE_MFR_SOFTSTART_CYCLE_COUNT/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_SOFTSTART_CYCLE_COUNT&31u));
	//PMBUS_CMD_SUPPORT_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_SOFTSTART_CYCLE_COUNT/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_SOFTSTART_CYCLE_COUNT&31u));

	/* initialize command structure for MFR_SOFTSTART_MAX_FREQUENCY. */
	// MFR_SOFTSTART_MAX_FREQUENCY COMMAND:
	ptr_pmbus_callback[PMBUS_CMDCODE_MFR_SOFTSTART_MAX_FREQUENCY] = PMBUS_HANDLE_MFR_SOFTSTART_MAX_FREQUENCY;
	//PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY.OPCODE = PMBUS_CMDCODE_MFR_SOFTSTART_MAX_FREQUENCY;
	//PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY.WRITE_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_WRITE;
	//PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY.READ_PROTOCOL = (uint8_t) TRANSACTION_PROTOCOL_READ;
	//PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY.NUM_BYTES = 2; // data only not including slave address and command
	//PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY.NUM_PROTOCOL_BYTES = 2;  // slave address command and any other non-data bytes
	//PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY.SUPPORTED = 1;
	//PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY.PROTECTED0 = 0;
	//PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY.PROTECTED1 = 0;
	//PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY.RANGE_TYPE = (uint8_t) PMBUS_RANGE_ALL;
	PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY.CMD_CONFIG = 0xc18223b4;
	PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY.DATA0 = &PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY.DATA1 = &PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY_DATA_LOOP0[0];  // set the pointer to the data array
	PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY_DATA_LOOP1 = &PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY_DATA_LOOP0[0];
	// RANGE SUPPORT for MFR_SOFTSTART_MAX_FREQUENCY COMMAND:
	// now populate pointers to the supported commands for each page
	PMBUS_CMD_ARRAY_LOOP[PMBUS_CMDCODE_MFR_SOFTSTART_MAX_FREQUENCY] = &PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY;
	//PMBUS_CMD_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_SOFTSTART_MAX_FREQUENCY] = &PMBUS_CMD_MFR_SOFTSTART_MAX_FREQUENCY;
	//lint -e{778} suppress "Constant expression evaluates to 0 in operation '&'" 
	PMBUS_CMD_SUPPORT_ARRAY_LOOP[PMBUS_CMDCODE_MFR_SOFTSTART_MAX_FREQUENCY/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_SOFTSTART_MAX_FREQUENCY&31u));
	//PMBUS_CMD_SUPPORT_ARRAY_LOOP1[PMBUS_CMDCODE_MFR_SOFTSTART_MAX_FREQUENCY/32] |= (uint32_t) ((uint32_t)1u << ((uint32_t)PMBUS_CMDCODE_MFR_SOFTSTART_MAX_FREQUENCY&31u));

}


