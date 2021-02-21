/*
 * patch_pmbus_stays_on.h
 *
 *  Created on: 27 Feb 2020
 *      Author: halimand
 */

#ifndef SRC_USER_APP_PATCH_PMBUS_STAYS_ON_H_
#define SRC_USER_APP_PATCH_PMBUS_STAYS_ON_H_

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

#include "patch_rom_table.h"
#include "string.h"
#include "add_on_features.h"
#include "uart_drv.h"                // uart driver functions
#include "pmbus_mfr_specific_handlers.h"
#include "regulation_drv.h"

void patch_Regulation_Shutdown_Sequence (PMBUS_PAGE_t loop, REGULATION_STATE state, REGULATION_CONTROLS control);
void patch_Regulation_Power_Mode (PMBUS_PAGE_t loop, REGULATION_STATE state);

#endif /* SRC_USER_APP_PATCH_PMBUS_STAYS_ON_H_ */
