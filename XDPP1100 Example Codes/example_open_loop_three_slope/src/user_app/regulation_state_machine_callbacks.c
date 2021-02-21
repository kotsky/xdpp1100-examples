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

#include "open_loop_llc.h"

USER_DATA_t user_data;

void regulation_sm_callbacks_init(void)
{
	/* Open Loop Soft Startup Example Modification Start */

	/* Set duty cycle forcing */
	// Enable FORCE DUTY
	PWM_RAMP0_FORCE_DUTY__RAMP0_FORCE_DUTY_EN__SET(1);
	PWM_RAMP1_FORCE_DUTY__RAMP1_FORCE_DUTY_EN__SET(1);

	// Force (update) duty to "0"
	PWM_RAMP0_FORCE_DUTY__RAMP0_FORCE_DUTY__SET(0);
	PWM_RAMP1_FORCE_DUTY__RAMP1_FORCE_DUTY__SET(0);

	// Set the callback functions for the regulation state machine.
	// To execute AT_SHUTDOWN() when XDPP1100 comes to REGULATION_STATE_AT_TARGET_VID / REGULATION_STATE_TOFF_FALL states
	// and does REGULATION_CONTROLS_SHUTDOWN / REGULATION_CONTROLS_SHUTDOWN_IMMEDIATE
	Regulation_set_regulation_event_cb(REGULATION_STATE_TOFF_FALL, REGULATION_CONTROLS_SHUTDOWN,
			AT_SHUTDOWN);

	Regulation_set_regulation_event_cb(REGULATION_STATE_TOFF_FALL, REGULATION_CONTROLS_SHUTDOWN_IMMEDIATE,
			AT_SHUTDOWN);

	Regulation_set_regulation_event_cb(REGULATION_STATE_AT_TARGET_VID, REGULATION_CONTROLS_SHUTDOWN,
			AT_SHUTDOWN);

	Regulation_set_regulation_event_cb(REGULATION_STATE_AT_TARGET_VID, REGULATION_CONTROLS_SHUTDOWN_IMMEDIATE,
			AT_SHUTDOWN);

	Regulation_set_regulation_event_cb(REGULATION_STATE_TON_DELAY, REGULATION_CONTROLS_TON_TOFF_DELAY_TIMER,
			AT_TON_DELAY);

	Regulation_set_fsw_irq_event_cb(fsw_irq_idx_5, open_loop_llc_soft_start_irq_handler);

	/* Open Loop Soft Startup Example Modification End */

}

void AT_TON_DELAY(PMBUS_PAGE_t loop)
{
	/* Open Loop Soft Startup Example Modification Start */

	user_data.shutdown_status = 0;
	open_loop_llc_soft_start_enable(loop);

	/* Open Loop Soft Startup Example Modification End */
}


/**
 * Function executes whenever the shutdown that was requested is completed.
 */

void AT_SHUTDOWN(PMBUS_PAGE_t loop)
{
	/* Open Loop Soft Startup Example Modification Start */

	// AT_SHUTDOWN() might be called several time, so to avoid that
	// shutdown_status will take care of one time call during shutdown
	if (user_data.shutdown_status == 0)
	{
		// Disable VOUT_UV faults
		// There was an observation that the UV FAULT is always turned on even when the converter stopped working.
		// By writing it at AT_SHUTDOWN, the UV FAULT status will be off.
		Faults_Mask_Fault(loop, 1, // hw fault
								0, // set_mask
								((1u<<(uint32_t)FAULT_TYPE_VOUT_UV_FAULT) |(1u<<(uint32_t)FAULT_TYPE_VOUT_UV_WARN))	// clear_mask
								);

		open_loop_llc_soft_start_disable(loop);

		VCONTROL_VC_VRAMP3__VC_VCONTROL_DELTA__SET((vcontrol_idx_t) loop, 0);
		user_data.shutdown_status = 1;
	}
	/* Open Loop Soft Startup Example Modification End */
}


