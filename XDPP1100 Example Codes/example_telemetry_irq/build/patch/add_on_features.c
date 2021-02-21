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
** Created on:  2020-08-19
*/

/* Standard library */
#include "telemetry_api.h"
#include "regulation_api.h"
#include "regulation_drv.h"
#include "faults_api.h"
#include "faults_drv.h"
#include "shasta_hal_tsen.h"
#include "shasta_hal_pwm.h"
#include "shasta_hal_pid.h"
#include "shasta_hal_analog.h"
#include "shasta_hal_common.h"
#include "shasta_hal_vcontrol.h"
#include "shasta_hal_isen.h"
#include "log_app.h"             /* Logging of errors */
#include <string.h>             /* memset */
#include "patch_rom_table.h"
#include "string.h"
#include "add_on_features.h"
#include "shasta_hal_tstctrl.h"  	// ate test state
#include "mmu_drv.h"                /* MMU_Initialization */
#include "driver_common.h"
#include "shasta_hal_fault_common.h"
#include "shasta_hal_fault.h"
#include "shasta_hal_vcontrol.h"
#include "pmbus_autogen.h"      // PMBUS_PAGE_t
#include "pmbus_mfr_autogen.h"

#include "regulation_state_machine_callbacks.h"
#include "telemetry_api.h"

void add_on_features_init (void)
{
	// write down here your input parameters
	for(uint8_t loop=0; loop < 2; loop++)	// for 2 loops to set the following:
	{
		user_data.vin_thresh_exponent[loop] = -2;   //Set the threshold exponent
//		user_data.fsw_target[loop] = LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(0, PMBUS_CMDCODE_FREQUENCY_SWITCH));	// desired frequency switch from GUI
		user_data.fsw_exp[loop] = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(0, PMBUS_CMDCODE_FREQUENCY_SWITCH));	// frequency switch exponent
		user_data.fsw_target[loop] = 250;		// frequency switch is set manually in format u11.0

		user_data.vin_threshold[loop] = 96;	//24V  in U11.2 - 96
		user_data.vin_hysteresis_threshold[loop] = 80;	//20V  in U11.2 - 96

		// set IRQ accordingly
		Telemetry_IRQ((PMBUS_PAGE_t)loop);
	}
}

/*
 * General Telemetry IRQ sequence of execution, based on VIN source
 */

void Telemetry_IRQ(PMBUS_PAGE_t loop)
{
	if(loop == 1)	// TELEM_IRQ8 in the use for loop1
	{
		// Setup and enable generic telemetry interrupt example
		Telemetry_Set_Irq_Threshold(TELEM_IRQ8, user_data.vin_threshold[loop], user_data.vin_thresh_exponent[loop]);
		Telemetry_Set_Irq_Hysteresis_Threshold(TELEM_IRQ8, user_data.vin_hysteresis_threshold[loop], user_data.vin_thresh_exponent[loop]);
		// page - loop 1 Selects the loop for reporting. PMBUS_PAGE_t
		// telemetry irq source - VIN loop 1 Telemetry_irq_src_t
		// generic telemetry irq number - TELEM_IRQ8 (12) Telemetry_IRQ_TYPE_t
		// set callback function - Telemetry_IRQ_VIN_HANDLE
		Telemetry_Setup_Irq(PMBUS_PAGE_1, VIN_1, TELEM_IRQ8, Telemetry_IRQ_VIN_HANDLE);

		//Setup and enable interrupt
		Telemetry_Enable_IRQ_Type(TELEM_IRQ8);
	}
	else	// TELEM_IRQ7 in the use for loop0
	{
		// Setup and enable generic telemetry interrupt example
		Telemetry_Set_Irq_Threshold(TELEM_IRQ7, user_data.vin_threshold[loop], user_data.vin_thresh_exponent[loop]);
		Telemetry_Set_Irq_Hysteresis_Threshold(TELEM_IRQ7, user_data.vin_hysteresis_threshold[loop], user_data.vin_thresh_exponent[loop]);

		// page - loop 0 Selects the loop for reporting. PMBUS_PAGE_t
		// telemetry irq source - VIN loop 0 Telemetry_irq_src_t
		// generic telemetry irq number - TELEM_IRQ7 (11) Telemetry_IRQ_TYPE_t
		// set callback function - Telemetry_IRQ_VIN_HANDLE
		Telemetry_Setup_Irq(PMBUS_PAGE_0, VIN_0, TELEM_IRQ7, Telemetry_IRQ_VIN_HANDLE);

		//Setup and enable interrupt
		Telemetry_Enable_IRQ_Type(TELEM_IRQ7);
	}
}

/**
 * Callback function for generic telemetry interrupt on VIN source.
 * Can be used to adjust deadtime or pid settings based on changes in VIN
 * @param Telemetry_type @ref Telemetry_IRQ_TYPE_t telemetry type to operate on
 */
void Telemetry_IRQ_VIN_HANDLE(Telemetry_IRQ_TYPE_t Telemetry_type)
{
	_Telemetry_s * Telemetry_str = Telemetry_GET_ARRAY_POINTER(Telemetry_type) ;
	//Grab the loop on which interrupt occurred
	PMBUS_PAGE_t loop = Telemetry_str->loop;

	// read actual frequency exponent
	user_data.fsw_exp[loop] = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_FREQUENCY_SWITCH));	// read actual frequency exponent

	if ((~Telemetry_str->polarity)&1)
	{
        //threshold
		custom_frequency_update(loop, user_data.fsw_target[loop], user_data.fsw_exp[loop]);
	}
	else	//else is executed when vin is above threshold
	{
		//Hysteresis threshold
		uint8_t frequency_offset = 20; // u11.0	or 10 in u11.-1
		custom_frequency_update(loop, user_data.fsw_target[loop] + frequency_offset, user_data.fsw_exp[loop]);
	}

}

/*
 * custom_frequency_update() updates frequency switch in XDPP1100 and
 * update its value in GUI
 */

void custom_frequency_update(PMBUS_PAGE_t loop, uint16_t frequency, int8_t frequency_exponent)
{
	Regulation_Switching_Frequency_Set(loop, frequency);	// set frequency internally

	// set frequency to GUI via PMBus command 0x33 PMBUS_CMDCODE_FREQUENCY_SWITCH
	uint16_t fs_target_linear11 = (uint16_t)(TWOS_COMPLEMENT(5, frequency_exponent) << 11) |          // exponent
		 (SHIFT_EXPONENT_UNSIGNED(frequency, -frequency_exponent));                             // mantissa
	PMBUS_Set_Command_Word(loop, PMBUS_CMDCODE_FREQUENCY_SWITCH, fs_target_linear11);
}


