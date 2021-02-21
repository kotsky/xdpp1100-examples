/*
 * open_loop_llc.c
/* ============================================================================
** Copyright (C) 2020 Infineon. All rights reserved.
**               Infineon Technologies, PSS SYS / DES
** ============================================================================
**
** ============================================================================
** This document contains proprietary information. Passing on and
** copying of this document, and communication of its contents is not
** permitted without prior written authorization.
** ============================================================================
**
** Created on:  2020-11-10
*/

/* Open Loop Soft Startup Example Modification Start */

#include "dtimer_drv.h"
#include "telemetry_drv.h"
#include "regulation_api.h"
#include "faults_api.h"
#include "faults_drv.h"
#include "pmbus_api.h"
#include "pmbus_gpio_control.h"
#include "shasta_hal_vsen.h"
#include "shasta_hal_vcontrol.h"
#include "shasta_hal_pwm.h"
#include "shasta_hal_pid.h"
//#include "shasta_hal_regulation.h"
#include "shasta_hal_scu.h"
#include "shasta_hal_cgu.h"
#include "shasta_hal_rgu.h"
#include "shasta_hal_telem.h"
#include "shasta_hal_common.h"
#include "shasta_hal_fault.h"
#include "shasta_hal_isen.h"
#include "regulation_state_machine_callbacks.h"
#include "pmbus_autogen.h"
#include "pmbus_mfr_autogen.h"
#include "user_app.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "cmsis_os_ext.h"                   // ARM::CMSIS:RTOS:Keil RTX ext
#include "log_app.h"             /* Logging of errors */
//#include "user_ntc_temperature_lut.h"
#include "patch_rom_table.h"
#include "string.h"
#include "add_on_features.h"
#include "uart_drv.h"                // uart driver functions
#include "pmbus_mfr_specific_handlers.h"

#include "open_loop_llc.h"


void update_force_duty(PMBUS_PAGE_t loop, uint8_t duty)
{
	if(loop == PMBUS_PAGE_0)
	{
		PWM_RAMP0_FORCE_DUTY__RAMP0_FORCE_DUTY__SET(duty);	//U0.8 // FORCE_DUTY
	}
	else
	{
		PWM_RAMP1_FORCE_DUTY__RAMP1_FORCE_DUTY__SET(duty);	//U0.8 // FORCE_DUTY
	}
}

void update_switching_period(PMBUS_PAGE_t loop, uint16_t period)
{
	if (loop == PMBUS_PAGE_0)
	{
		PWM_RAMP0_TSWITCH0__TSWITCH0__SET(period);
	}
	else
	{
		PWM_RAMP1_TSWITCH1__TSWITCH1__SET(period);
	}
}

void open_loop_llc_soft_start_enable(PMBUS_PAGE_t loop)
{
	uint16_t max_freq_khz, steady_freq_khz;
	int32_t max_freq_exp, steady_freq_exp;

	// 1. Get Maximum Switching Frequency from MFR_SOFTSTART_MAX_FREQUENCY command
	max_freq_khz = PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_MFR_SOFTSTART_MAX_FREQUENCY);
	max_freq_khz = (uint16_t)LINEAR11_TO_MANTISSA(max_freq_khz);  // since we know exponent is 0 we can just grab mantissa
	max_freq_exp = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_MFR_SOFTSTART_MAX_FREQUENCY));
	max_freq_khz = (uint16_t)SHIFT_EXPONENT(max_freq_khz, max_freq_exp);

	// 2. Get Steady State Switching Frequency from FREQUENCY_SWITCH command
	steady_freq_khz = PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_FREQUENCY_SWITCH);
	steady_freq_khz = (uint16_t)LINEAR11_TO_MANTISSA(steady_freq_khz);  // since we know exponent is 0 we can just grab mantissa
	steady_freq_exp = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_FREQUENCY_SWITCH));
	steady_freq_khz = (uint16_t)SHIFT_EXPONENT(steady_freq_khz, steady_freq_exp);

	if (max_freq_khz == 0)
	{
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

	update_switching_period(loop, user_data.freq_max_period);

	// Enable FORCE DUTY
	PWM_RAMP0_FORCE_DUTY__RAMP0_FORCE_DUTY_EN__SET(1);
	PWM_RAMP1_FORCE_DUTY__RAMP1_FORCE_DUTY_EN__SET(1);

	// Force (update) duty
	update_force_duty(loop, 0);

	// SET initial Phase to 0
	user_data.softstart_current_phase = 0;

	// SET sofstart counter
	user_data.softstart_counter = 0;
	user_data.softstart_pwm_duty = 0;

	// Get MAX_DUTY
	int32_t max_duty_man = LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(loop,PMBUS_CMDCODE_MAX_DUTY));
	int32_t max_duty_exp = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(loop,PMBUS_CMDCODE_MAX_DUTY));
	uint32_t max_duty = (uint32_t)SHIFT_EXPONENT(max_duty_man, (max_duty_exp - RAMP_DC_MAX_EXPONENT));
	if (max_duty > 0xFF) max_duty = 0xFF;

	user_data.softstart_max_duty = (max_duty * NUM_FORMAT_DIFF_RATIO) >> NUM_FORMAT_DIFF_RATIO_SCALE;

	// Enable switching Interrupt and irq rate
	Regulation_setup_fsw_irq(loop, fsw_irq_idx_5, user_data.softstart_irq_rate_sel);

	// Disable Interrupt if max frequency value < steady_state frequency.
	// Frequency is inversely proportional to period
	// if-else condition is max_freq_period > steady_state_freq_period
	if (user_data.freq_max_period > user_data.freq_switch_period)
	{
		// Force (update) duty
		update_force_duty(loop, 0);

		// Disable switching Interrupt
		Regulation_setup_fsw_irq(loop, fsw_irq_idx_5, fsw_irq_rate_sel_disabled);
	}
}

void open_loop_llc_soft_start_disable(PMBUS_PAGE_t loop)
{
	// SET initial Phase to 0
	user_data.softstart_current_phase = 0;

	// SET sofstart counter
	user_data.softstart_counter = 0;
	user_data.softstart_pwm_duty = 0;

	// Enable FORCE DUTY
	PWM_RAMP0_FORCE_DUTY__RAMP0_FORCE_DUTY_EN__SET(1);
	PWM_RAMP1_FORCE_DUTY__RAMP1_FORCE_DUTY_EN__SET(1);

	// Force (update) duty
	update_force_duty(loop, 0);

	// Disable switching Interrupt
	Regulation_setup_fsw_irq(loop, fsw_irq_idx_5, fsw_irq_rate_sel_disabled);
}

void open_loop_llc_soft_start_irq_handler(PMBUS_PAGE_t loop)
{
	// Frequency is inversely proportional to period
	// if-else condition is max_freq_period > steady_state_freq_period
	if (!(user_data.freq_max_period > user_data.freq_switch_period))
	{
		if(user_data.softstart_current_phase < SOFTSTART_MAX_STAGE)
		{
			// Increment softstart cycle counter
			user_data.softstart_counter++;

			// Make sure PWM duty is below Max Duty
			if (user_data.softstart_pwm_duty < user_data.softstart_max_duty)
			{
				// Increment duty cycle based on the specified stepsize
				user_data.softstart_pwm_duty += user_data.softstart_pwm_stepsize[user_data.softstart_current_phase];
			}

			// Update duty cycle with Force Duty
			update_force_duty(loop, user_data.softstart_pwm_duty);

			// Check if softstart cycle counter hits the assigned cycle count at each phase
			if (user_data.softstart_counter >= user_data.softstart_cycle_count[user_data.softstart_current_phase])
			{
				user_data.softstart_current_phase++;	// Increase softstart current phase
				user_data.softstart_counter = 0;		// Reset softstart counter
			}
		}

		// Check if current phase exceed the maximum stage possible
		else
		{
			// If need for frequency modulation, this should be the place to program.

			// For frequency ramp down, the period of Freq_Switch must be more than the Freq_Max.
			if (user_data.freq_switch_period > user_data.freq_ramp_counter)  // freq_ramp_counter already set as Freq_Max during initialization.
			{
				user_data.freq_ramp_counter++;  // freq_ramp_counter is incremented until it reaches freq_switch_period
				update_switching_period(loop, user_data.freq_ramp_counter);
			}
			else
			{
				Regulation_setup_fsw_irq(loop, fsw_irq_idx_5, fsw_irq_rate_sel_disabled);  // Disable switching Interrupt
			}
		}
	}
}

/* Open Loop Soft Startup Example Modification End */
