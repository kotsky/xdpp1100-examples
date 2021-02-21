/*
 * vin_pulse_kickstart.c
 *
 *  Created on: 15 Jul 2019
 *      Author: halimand
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
#include "shasta_hal_tsen.h"
#include "regulation_api.h"
#include "vin_pulse_kickstart.h"

/**
 * Function to set the PID to generate a fixed duty cycle
 * @param loop select the operating loop
 * @param duty Set the duty cycle
 */
void force_PID_dutycycle(PMBUS_PAGE_t loop, uint32_t duty)
{
	// Forced Duty Cycle Value override. // Format = U0.8. Min = 0. Max = 0.9961. LSB = 3.906e-3
	PID_PID_FORCE__PID_FORCE_DUTY__SET((pid_idx_t)loop, duty); // dutycycle = duty

	// ENABLE forced duty cycle
	PID_PID_FORCE__PID_FORCE_DUTY_EN__SET((pid_idx_t)loop, 1);

	for(uint16_t i = 0; i < 2; i++); // For-loop delay before disabling forced duty cycle

	// Forced Duty Cycle Value override. // Format = U0.8. Min = 0. Max = 0.9961. LSB = 3.906e-3
	PID_PID_FORCE__PID_FORCE_DUTY__SET((pid_idx_t)loop, 0); // // dutycycle = 0
}

/**
 * Function to initialize and start the kickstart pulse
 * @param loop select the operating loop
 * @param pulse_width_ns set the duty cycle in pulse width
 * @param freq_khz set the switching frequency in khz
 */
void pulse_kickstart(PMBUS_PAGE_t loop, uint16_t pulse_width_ns, uint16_t freq_khz)
{
	// Set Switching Frequency for pulse kickstart. API can be found on regulation_api.h
	Regulation_Switching_Frequency_Set(loop, freq_khz); //100 kHz, Period = 0.01ms = 10us = 10,000ns

	// calculate mininum pulse needed from vrs_track_start_thr
	uint16_t vrs_track_start_thr = COMMON_VRS_CFG__VRS_TRACK_START_THR__GET();
	uint32_t min_pulse_ns = vrs_track_start_thr*10;

	// calculate period_in_ns
	uint32_t period_ns = 1000000/freq_khz;

	// Initialize forced_duty to zero
	uint32_t forced_duty = 0;

	// if desired_pulse_ns < period_in_ns, update forced_duty
	if(pulse_width_ns < period_ns && pulse_width_ns > min_pulse_ns)
	{
		// translate desired_pulse_ns/period_in_ns to duty_cycle_percentage and calculate forced_duty in hex
		forced_duty = (pulse_width_ns*0xFF)/period_ns;
	}

	// Pulse kickstart by forcing PID duty
	force_PID_dutycycle(loop, forced_duty);
}

/**
 * Function to release force PID duty cycle
 * @param loop select the operating loop
 */
void release_PID_dutycycle(PMBUS_PAGE_t loop)
{
	// Get user configuration from PMBus
	uint16_t freq_khz = PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_FREQUENCY_SWITCH);

	// Convert LINEAR11 to mantissa and exponent
	int32_t freq_khz_man = (uint16_t)LINEAR11_TO_MANTISSA(freq_khz);
	int32_t freq_khz_exp = LINEAR11_TO_EXPONENT(freq_khz);
	freq_khz = (uint16_t)SHIFT_EXPONENT(freq_khz_man, freq_khz_exp);

	// Update Switching frequency with the user configuration from PMBus
	Regulation_Switching_Frequency_Set(loop, freq_khz);

	// DISABLE forced duty cycle
	PID_PID_FORCE__PID_FORCE_DUTY_EN__SET((pid_idx_t)loop, 0);
}

/**
 * Function to force feedforward to 0 to remove its influence on the generated dutycycle
 * @param loop select the operating loop
 */
void force_feedforward(PMBUS_PAGE_t loop)
{
	// Set FeedForward to VRECT since beginning, instead of vrs_voltage_init
	PID_PID_FF_CFG1__PID_FF_VRECT_SEL__SET((pid_idx_t)loop, 0);

	// Enable FeedForward Override
	PID_PID_FF_CFG4__PID_FF_OVERRIDE_SEL__SET((pid_idx_t)loop, 1);

	// Set FeedForward value to 0
	PID_PID_FF_CFG4__PID_FF_OVERRIDE__SET((pid_idx_t)loop, 0);
}

/**
 * Function to release the force feedforward that was set 0
 * @param loop select the operating loop
 */
void release_feedforward(PMBUS_PAGE_t loop)
{
	// Disable FeedForward Override
	PID_PID_FF_CFG4__PID_FF_OVERRIDE_SEL__SET((pid_idx_t)loop, 0);
}
