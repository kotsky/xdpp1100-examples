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


void regulation_sm_callbacks_init(void)
{
	// Set the callback functions for the regulation state machine.
	// Example:
	Regulation_set_regulation_event_cb(REGULATION_STATE_AT_TARGET_VID, REGULATION_CONTROLS_ENABLE,
				AT_TARGET_ENABLE);
	// to execute AT_TARGET_ENABLE() when XDPP1100 comes to REGULATION_STATE_AT_TARGET_VID state and does REGULATION_CONTROLS_ENABLE
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
	/* Hola Mundo Example Modification Start */
	hola_mundo();
	/* Hola Mundo Example Modification End */
}

void AT_SHUTDOWN(PMBUS_PAGE_t loop)
{
	VCONTROL_VC_VRAMP3__VC_VCONTROL_DELTA__SET((vcontrol_idx_t) loop, 0);
}


