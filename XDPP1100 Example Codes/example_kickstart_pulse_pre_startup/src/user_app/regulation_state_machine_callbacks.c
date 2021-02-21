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
/* Kickstart Pulse Pre-Startup Example Modification Start */
#include "vin_pulse_kickstart.h"
/* Kickstart Pulse Pre-Startup Example Modification End */

USER_DATA_t user_data;

#define FAULT_TYPE_EXTERNAL fw_spare1


void regulation_sm_callbacks_init(void)
{
	// Set the callback functions for the regulation state machine.
	// Example:
	Regulation_set_regulation_event_cb(REGULATION_STATE_AT_TARGET_VID, REGULATION_CONTROLS_ENABLE,
				AT_TARGET_ENABLE);
	// to execute AT_TARGET_ENABLE() when XDPP1100 comes to REGULATION_STATE_AT_TARGET_VID state and does REGULATION_CONTROLS_ENABLE

	/* Kickstart Pulse Pre-Startup Example Modification Start */
	Regulation_set_regulation_event_cb(REGULATION_STATE_TON_DELAY, REGULATION_CONTROLS_TON_TOFF_DELAY_TIMER,
				AT_PRESTARTUP);
	Regulation_set_regulation_event_cb(REGULATION_STATE_OFF, REGULATION_CONTROLS_SHUTDOWN,
				AT_SHUTDOWN);
	Regulation_set_regulation_event_cb(REGULATION_STATE_OFF, REGULATION_CONTROLS_SHUTDOWN_IMMEDIATE,
				AT_SHUTDOWN);
	/* Kickstart Pulse Pre-Startup Example Modification End */
}

void TON_RISE_VID_REACHED(PMBUS_PAGE_t loop)
{

}

void TON_DELAY_ENABLE(PMBUS_PAGE_t loop)
{


}

void TON_RISE_ENABLE(PMBUS_PAGE_t loop)
{

}

void AT_TARGET_ENABLE(PMBUS_PAGE_t loop)
{

}

void AT_SHUTDOWN(PMBUS_PAGE_t loop)
{
	VCONTROL_VC_VRAMP3__VC_VCONTROL_DELTA__SET((vcontrol_idx_t) loop, 0);

	/* Kickstart Pulse Pre-Startup Example Modification Start */
	PWM_MAX_DUTY_SCALE__RAMP0_DC_MAX_NOM__SET(0);
	PWM_MAX_DUTY_SCALE__RAMP1_DC_MAX_NOM__SET(0);
	release_PID_dutycycle(loop);
	force_feedforward(loop);
	/* Kickstart Pulse Pre-Startup Example Modification End */
}

/**
 * Kickstart Pulse Pre-Startup Example Function
 * Function to enable kickstart duty cycle at TON_Delay
 * @param loop select the operating loop
 */
void AT_PRESTARTUP(PMBUS_PAGE_t loop)
{
	// Pulse kickstart just enough to enable VRECT (VIN measurement)
	pulse_kickstart(loop, 810, 100); //pulse width = 810ns, freq = 100kHz

	// Prolong TON_DELAY state by 50us to discharge output capacitor
	sys_delay_by_us(50);

	release_PID_dutycycle(loop);
	release_feedforward(loop);
}

