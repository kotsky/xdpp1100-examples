/*
 * pmbus_mfr_specific_handlers.c
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

#include "fw_config.h"           /* Essential fw-wide configuration for e.g. buffer size #defines */
#include "environment.h"         /* STATIC, */
#include <stdint.h>              /* uint*_t */
#include <string.h>				 /* memcpy */
#include "fw_bool.h"             /* boolean type */
#include "pmbus_mfr_specific_handlers.h"
#include "pmbus_api.h"
#include "regulation_drv.h"
#include "pmbus_autogen.h"
#include "pmbus_mfr_autogen.h"

// debug headers:
#include "shasta_hal_scu.h"
#include "shasta_hal_cgu.h"
#include "shasta_hal_rgu.h"
#include "shasta_hal_telem.h"
#include "shasta_hal_fan.h"
#include "shasta_hal_trim.h"
#include "shasta_hal_vsen.h"
#include "regulation_api.h"
#include "faults_api.h"
#include "faults_drv.h"
#include "regulation_drv.h"
#include "telemetry_drv.h"
#include "pmbus_drv.h"
#include "driver_common.h"
#include "log_app.h"
#include "regulation_state_machine_callbacks.h"
#include "add_on_features.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "uart_drv.h"
#include "user_app.h"

#include "open_loop_llc.h"

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
*/

/* Open Loop Soft Startup Example Modification Start */

void PMBUS_HANDLE_MFR_SOFTSTART_IRQ_RATE_SEL(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	if ((direction == PMBUS_WRITE)||(direction == OTP_RESTORE)) {

		uint8_t irq_rate_sel = PMBUS_Get_Command_Byte(page, PMBUS_CMDCODE_MFR_SOFTSTART_IRQ_RATE_SEL);

		if (irq_rate_sel >= 3 && irq_rate_sel < 7) {
			user_data.softstart_irq_rate_sel = irq_rate_sel;
		}
		else {
			user_data.softstart_irq_rate_sel = 0x07;
		}
	}
}

void PMBUS_HANDLE_MFR_SOFTSTART_PWM_STEPSIZE(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	if ((direction == PMBUS_WRITE)||(direction == OTP_RESTORE)) {
		// 1. Get cycle counts from pmbus array. Format is direct 8-bit.
		uint8_t *pPWMStepSizeArrayPtr = PMBUS_GET_DATA_ARRAY_POINTER(page, PMBUS_CMDCODE_MFR_SOFTSTART_PWM_STEPSIZE);

		if (pPWMStepSizeArrayPtr != NULL) {
			// 2. Assign to user_data structure for storage.
			for (uint8_t i=0; i < SOFTSTART_MAX_STAGE; i++){
				if (pPWMStepSizeArrayPtr[i] != 0 || pPWMStepSizeArrayPtr[i] != 0xFF ) {
					user_data.softstart_pwm_stepsize[i] = pPWMStepSizeArrayPtr[i];
				}
				else {
					user_data.softstart_pwm_stepsize[i] = 0x01;
				}
			}
		}
	}
}

void PMBUS_HANDLE_MFR_SOFTSTART_CYCLE_COUNT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	if ((direction == PMBUS_WRITE)||(direction == OTP_RESTORE)) {
		// 1. Get cycle counts from pmbus array. Format is direct 8-bit.
		uint8_t *pCycleCountArrayPtr = PMBUS_GET_DATA_ARRAY_POINTER(page, PMBUS_CMDCODE_MFR_SOFTSTART_CYCLE_COUNT);

		if (pCycleCountArrayPtr != NULL) {
			// 2. Assign to user_data structure for storage.
			for (uint8_t i=0; i < SOFTSTART_MAX_STAGE; i++){
				if (pCycleCountArrayPtr[i] != 0 || pCycleCountArrayPtr[i] != 0xFF) {
					user_data.softstart_cycle_count[i] = pCycleCountArrayPtr[i];
				}
				else {
					user_data.softstart_cycle_count[i] = 0x55;
				}
			}
		}
	}
}

void PMBUS_HANDLE_MFR_SOFTSTART_MAX_FREQUENCY(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	uint16_t max_freq_khz, steady_freq_khz;
	int32_t max_freq_exp, steady_freq_exp;

	if ((direction == PMBUS_WRITE)||(direction == OTP_RESTORE))  // on writes change the switching frequency of the loop
	{
		// 1. Get Maximum Switching Frequency from MFR_SOFTSTART_MAX_FREQUENCY command
		max_freq_khz = PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_MFR_SOFTSTART_MAX_FREQUENCY);
		max_freq_khz = (uint16_t)LINEAR11_TO_MANTISSA(max_freq_khz);  // since we know exponent is 0 we can just grab mantissa
		max_freq_exp = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_MFR_SOFTSTART_MAX_FREQUENCY));
		max_freq_khz = (uint16_t)SHIFT_EXPONENT(max_freq_khz, max_freq_exp);

		// 2. Get Steady State Switching Frequency from FREQUENCY_SWITCH command
		steady_freq_khz = PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_FREQUENCY_SWITCH);
		steady_freq_khz = (uint16_t)LINEAR11_TO_MANTISSA(steady_freq_khz);  // since we know exponent is 0 we can just grab mantissa
		steady_freq_exp = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_FREQUENCY_SWITCH));
		steady_freq_khz = (uint16_t)SHIFT_EXPONENT(steady_freq_khz, steady_freq_exp);

		if (max_freq_khz == 0) {
			max_freq_khz = steady_freq_khz;
		}

		// 3. Calculate the period of the Max Switching Frequency
		uint32_t max_freq_period = 1000000/(max_freq_khz*SWITCHING_PERIOD_LSB_NS);
		if (max_freq_period > 0x1ff) max_freq_period = 0x1ff;

		// 4. Calculate the period of the Steady State Switching Frequency
		uint32_t steady_freq_period = 1000000/(steady_freq_khz*SWITCHING_PERIOD_LSB_NS);
		if (steady_freq_period > 0x1ff) steady_freq_period = 0x1ff;

		// 5. Assign max_freq_period to user_data
		user_data.freq_max_period = (uint16_t) max_freq_period;

		// 6. Also assign freq_ramp_counter to user_data
		user_data.freq_ramp_counter = user_data.freq_max_period;

		// 7. Assign steady_state_frequency_period to user_data
		user_data.freq_switch_period = (uint16_t) steady_freq_period;

		// 8. Update Switching Period to TSWITCH register
		update_switching_period(page, max_freq_period); // Use Max Freq as startup switching frequency

		// commands dependent on frequency switch:
		PMBUS_HANDLE_MAX_DUTY(page, direction);
	}
}

/* Open Loop Soft Startup Example Modification End */
