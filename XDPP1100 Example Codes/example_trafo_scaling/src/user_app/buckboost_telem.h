/*
 * buckboost_telem.h
 *
 *  Created on: 17 Jan 2020
 *      Author: halimand
 */

#ifndef SRC_USER_APP_BUCKBOOST_TELEM_H_
#define SRC_USER_APP_BUCKBOOST_TELEM_H_

/* Compiler configurations first */
#include "fw_config.h"           /* Essential fw-wide configuration for e.g. buffer size #defines */
#include "patch_run.h"          /* checking for function patch points */
#include "environment.h"         /* STATIC, INLINE */
#include "shasta.h"
#include "system_shasta.h"
#include "log_app.h"            // Logging of errors
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX

/* Always compare to the associated interface */
#include "telemetry_drv.h"
#include "telemetry_api.h"
#include "telemetry_irq_handlers.h"
#include "faults_api.h"
#include "regulation_drv.h"
#include "pmbus_api.h"
//#include "shasta_hal_telem.h"
#include "shasta_hal_scu.h"
#include "shasta_hal_cgu.h"
#include "shasta_hal_rgu.h"
#include "shasta_hal_telem.h"
#include "shasta_hal_telem_common.h"
#include "shasta_hal_fan.h"
#include "shasta_hal_pid.h"
#include "shasta_hal_tsen.h"
#include "shasta_hal_common.h"
#include "shasta_hal_fault.h"
/* Standard library */
#include <stdint.h>              /* uint*_t */
#include "fw_bool.h"             /* boolean type */

#include "pmbus_mfr_autogen.h"

void patch_Telemetry_change_scales(PMBUS_PAGE_t loop);

#endif /* SRC_USER_APP_BUCKBOOST_TELEM_H_ */
