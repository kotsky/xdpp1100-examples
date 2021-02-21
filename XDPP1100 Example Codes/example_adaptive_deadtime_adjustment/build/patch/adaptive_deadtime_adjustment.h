/*
 * adaptive_deadtime_adjustment.h
 *
 *  Created on: 20 Feb 2020
 *      Author: halimand
 */

#ifndef SRC_USER_APP_ADAPTIVE_DEADTIME_ADJUSTMENT_H_
#define SRC_USER_APP_ADAPTIVE_DEADTIME_ADJUSTMENT_H_

#include "pmbus_autogen.h"      // PMBUS_PAGE_t
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
#include "pmbus_mfr_autogen.h"
#include "regulation_state_machine_callbacks.h"

void adaptive_deadtime_init(PMBUS_PAGE_t loop);
void adaptive_deadtime_adjustment(PMBUS_PAGE_t loop);

#endif /* SRC_USER_APP_ADAPTIVE_DEADTIME_ADJUSTMENT_H_ */
