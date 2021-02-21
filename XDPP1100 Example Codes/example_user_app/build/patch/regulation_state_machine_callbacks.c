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
#include "pmbus_autogen.h"      // PMBUS_PAGE_t
#include "pmbus_mfr_autogen.h"
#include "dtimer_drv.h"
#include "telemetry_api.h"
#include "telemetry_irq_handlers.h"
#include "regulation_api.h"
#include "regulation_drv.h"
#include "faults_api.h"
#include "faults_drv.h"
#include "pmbus_api.h"
#include "pmbus_gpio_control.h"
#include "shasta_hal_vsen.h"
#include "shasta_hal_vcontrol.h"
#include "shasta_hal_pwm.h"
#include "shasta_hal_pid.h"
#include "shasta_hal_scu.h"
#include "shasta_hal_cgu.h"
#include "shasta_hal_rgu.h"
#include "shasta_hal_telem.h"
#include "shasta_hal_common.h"
#include "shasta_hal_fault.h"
#include "shasta_hal_isen.h"
#include "regulation_state_machine_callbacks.h"
#include "log_app.h"             /* Logging of errors */
#include "periodic_functions.h"
#include "patch_rom_table.h"
#include "shasta_hal_fault.h"
#include "shasta_hal_fault_common.h"
#include "add_on_features.h"

USER_DATA_t user_data;

#define FAULT_TYPE_EXTERNAL fw_spare1

void loadline_adjustment(PMBUS_PAGE_t loop, uint32_t mohms);


void regulation_sm_callbacks_init(void)
{
	// Set the callback functions for the regulation state machine.
	// ------------------------------------------------------------------------------------------------------------
	Regulation_set_regulation_event_cb(REGULATION_STATE_AT_TARGET_VID, REGULATION_CONTROLS_ENABLE,
			AT_TARGET_ENABLE);

#ifdef frequency_dither
	Regulation_set_regulation_event_cb(REGULATION_STATE_TOFF_FALL, REGULATION_CONTROLS_SHUTDOWN,
			frequency_dither_disable);

	Regulation_set_regulation_event_cb(REGULATION_STATE_TOFF_FALL, REGULATION_CONTROLS_SHUTDOWN_IMMEDIATE,
			frequency_dither_disable);
#endif
#ifdef en_ishare
	Regulation_set_regulation_event_cb(REGULATION_STATE_TON_RISE, REGULATION_CONTROLS_ENABLE,
			TON_RISE_ENABLE);
#endif

	Regulation_set_regulation_event_cb(REGULATION_STATE_TON_DELAY, REGULATION_CONTROLS_TON_TOFF_DELAY_TIMER,
			TON_DELAY_ENABLE);


	#ifdef en_ishare
	Regulation_set_regulation_event_cb(REGULATION_STATE_OFF, REGULATION_CONTROLS_SHUTDOWN,
			AT_SHUTDOWN);

	Regulation_set_regulation_event_cb(REGULATION_STATE_OFF, REGULATION_CONTROLS_SHUTDOWN_IMMEDIATE,
			AT_SHUTDOWN);
	#endif
	#ifdef en_ishare
	Regulation_set_regulation_event_cb(REGULATION_STATE_TON_RISE, REGULATION_CONTROLS_VID_REACHED,
			TON_RISE_VID_REACHED);
	#endif


	// ------------------------------------------------------------------------------------------------------------

	// register the callback functions for fsw interrupts
#ifdef en_ishare
	Regulation_set_fsw_irq_event_cb(fsw_irq_idx_2, remove_added_droop_irq_callback);
#endif

#ifdef frequency_dither
	Regulation_set_fsw_irq_event_cb(fsw_irq_idx_3, frequency_dither_irq_callback);
#endif
#ifdef ramp_switching_frequency_pcmc_startup
	Regulation_set_fsw_irq_event_cb(fsw_irq_idx_4, ramp_switching_frequency_pcmc_startup_irq_handle);
#endif

	// Setup and enable generic telemetry interrupt example
	user_data.VIN_Thresh_Exponent = -2;   //Set the threshold exponent
	Telemetry_Set_Irq_Threshold(TELEM_IRQ7, 96, user_data.VIN_Thresh_Exponent); //24V  in U11.2 - 96
	Telemetry_Set_Irq_Hysteresis_Threshold(TELEM_IRQ7, 80, user_data.VIN_Thresh_Exponent); //20V  in U11.2 - 96

	// page - loop 0 Selects the loop for reporting. PMBUS_PAGE_t
	// telemetry irq source - VIN loop 0 Telemetry_irq_src_t
	// generic telemetry irq number - TELEM_IRQ7 (11) Telemetry_IRQ_TYPE_t
	// set callback function - Telemetry_IRQ_VIN_HANDLE
	Telemetry_Setup_Irq(PMBUS_PAGE_0, VIN_0, TELEM_IRQ7, Telemetry_IRQ_VIN_HANDLE);
	//Setup and enable interrupt
	// page - loop 1 Selects the loop for reporting. PMBUS_PAGE_t
	// telemetry irq source - VIN loop 1 Telemetry_irq_src_t
	// generic telemetry irq number - TELEM_IRQ8 (12) Telemetry_IRQ_TYPE_t
	// set callback function - Telemetry_IRQ_VIN_HANDLE
	Telemetry_Setup_Irq(PMBUS_PAGE_1, VIN_1, TELEM_IRQ8, Telemetry_IRQ_VIN_HANDLE);


	//Example of setting up the response on external fault to FAULT_RESPONSE_RETRY_SHUTDOWN with 6 hiccups
	//with no hysteresis

	FAULTS_SETUP_FAULT(
			PMBUS_PAGE_0 ,  //PMBUS_PAGE_t pmbus page to update status on
			FAULT_TYPE_EXTERNAL,
			0xB0, //fault response byte: Response[7:6], Retry_Setting{5:3] and Delay_Time[2:0]
			FAULTS_CONFIG_VOUT_DELAY_UNIT, //Config_Delay_Unit This is used to decode the fields in FW_CONFIG_FAULTS PMBUS command (Time unit for retry responses)
			VOLTAGE_RESPONSE_TYPE, //response_config This is used to decode response command byte. Voltage(Temp, TON MAX) type or CURRENT type response
			(uint8_t)PMBUS_CMDCODE_STATUS_MFR_SPECIFIC, //pmbus_status_command status command number STATUS_XXX used for reporting the fault on pmbus
			(uint8_t)PMBUS_STATUS_MFR_SPECIFIC_0, //pmbus_status_bit_position bit position in command STATUS_XXX used for reporting the fault on pmbus
			(FAULT_TYPE_t) FAULT_TYPE_EXTERNAL); //hysteresis sets the hysteresis FAULT_TYPE_t


}
#ifdef en_ishare
void TON_RISE_VID_REACHED(PMBUS_PAGE_t loop)
{
	added_droop_enable(loop);
}

void TON_DELAY_ENABLE(PMBUS_PAGE_t loop){

#ifdef ramp_switching_frequency_pcmc_startup
	ramp_switching_frequency_pcmc_startup_enable(loop);
#endif

}

void TON_RISE_ENABLE(PMBUS_PAGE_t loop)
{
#ifdef en_ishare
	enable_ishare(loop);
#endif
}
#endif
void AT_TARGET_ENABLE(PMBUS_PAGE_t loop)
{
#ifdef frequency_dither
	frequency_dither_enable(loop);
#endif
}

void AT_SHUTDOWN(PMBUS_PAGE_t loop)
{
#ifdef ramp_switching_frequency_pcmc_startup
	ramp_switching_frequency_pcmc_startup_disable(loop);
#endif

#ifdef en_ishare
	disable_ishare(loop);
#endif

	VCONTROL_VC_VRAMP3__VC_VCONTROL_DELTA__SET((vcontrol_idx_t) loop, 0);
}

/**
 * Callback function for generic telemetry interrupt on VIN source.
 * Can be used to adjust deadtime or pid settings based on changes in VIN
 * @param Telemetry_type @ref Telemetry_IRQ_TYPE_t telemetry type to operate on
 */
void Telemetry_IRQ_VIN_HANDLE(Telemetry_IRQ_TYPE_t Telemetry_type) {

	_Telemetry_s * Telemetry_str = Telemetry_GET_ARRAY_POINTER(Telemetry_type) ;
	//Grab the loop on which interrupt occurred
	//uint8_t loop = Telemetry_str->loop;

	if ((~Telemetry_str->polarity)&1) {
        //threshold
	}
	else {
		//Hysteresis threshold
	}

}

/**
 * example of loadline adjustment with PMBUS_Q_EXP
 * @param loop pmbus page to operate on
 * @param mohms @ref PMBUS_Q_EXP format number in mohms
 */
void loadline_adjustment(PMBUS_PAGE_t loop, uint32_t mohms)
{
	uint32_t data;
	// convert from PMBUS_Q_EXP to LOADLINE_EXP
	data = (uint32_t)SHIFT_EXPONENT((int32_t)mohms, (PMBUS_Q_EXP - LOADLINE_EXP));
	// convert to linear11 format, 5bit exponent, 11bit mantissa
	data = (uint32_t)(((uint32_t)TWOS_COMPLEMENT (5, LOADLINE_EXP)<<11) | (data & 0x3ff));  // unsigned is 0x3ff
	PMBUS_Set_Command_Word((PMBUS_PAGE_W_BROADCAST_t)loop, PMBUS_CMDCODE_VOUT_DROOP, (uint16_t)data);
	// send a pmbus command update to vout_command to execute callback on command:
	PMBUS_Inter_Thread_Set_Command((PMBUS_PAGE_W_BROADCAST_t)loop,
			PMBUS_CMDCODE_VOUT_DROOP, PMBUS_WRITE);
}

/**
 * Function for reporting both an error to log buffer and pmbus status.
 * This can only be used for non fatal runtime errors that can be recoverable.
 * source is always USER type @ref Log_Source_t.
 * @param program_counter Current program counter logged.  Usually pass PROGRAM_COUNTER
 * @param cml_status @ref PMBUS_CML_STATUS_e cml error type defined by pmbus spec, value
 * provided will be used as the bit to set in STATUS_CML pmbus command
 */
void USER_Log_Error(uint32_t program_counter, PMBUS_CML_STATUS_e cml_status)
{
	PMBUS_Log_Error(USER, program_counter, cml_status);
}


