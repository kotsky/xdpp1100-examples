/*
 * iout_scaling_pmbus_mfr_handler.h
 *
 *  Created on: 31 Oct 2019
 *      Author: halimand
 */

#ifndef SRC_USER_APP_IOUT_RANGE_PMBUS_MFR_HANDLER_H_
#define SRC_USER_APP_IOUT_RANGE_PMBUS_MFR_HANDLER_H_

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
#include "shasta_hal_vcontrol.h"
#include "shasta_hal_isen.h"
#include "shasta_hal_scu.h"
#include "shasta_hal_cgu.h"
#include "shasta_hal_rgu.h"
#include "shasta_hal_telem.h"
//#include "shasta_hal_fan.h"
//#include "shasta_hal_trim.h"
#include "shasta_hal_vsen.h"
#include "regulation_api.h"
#include "faults_api.h"
#include "faults_drv.h"
#include "regulation_drv.h"
#include "telemetry_drv.h"
#include "pmbus_drv.h"



void patch_PMBUS_HANDLE_IOUT_CAL_OFFSET(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction);
void patch_PMBUS_HANDLE_IOUT_OC_FAULT_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction);
void patch_PMBUS_HANDLE_IOUT_UC_FAULT_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction);
void patch_PMBUS_HANDLE_IOUT_OC_WARN_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction);
void patch_PMBUS_HANDLE_IIN_OC_FAULT_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction);
void patch_PMBUS_HANDLE_IIN_OC_WARN_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction);
void patch_PMBUS_HANDLE_VOUT_DROOP(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction);
void patch_PMBUS_HANDLE_FW_CONFIG_REGULATION(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction);
void patch_PMBUS_HANDLE_MFR_IOUT_OC_FAST_FAULT_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction);
void patch_PMBUS_HANDLE_MFR_IOUT_APC(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction);


#endif /* SRC_USER_APP_IOUT_RANGE_PMBUS_MFR_HANDLER_H_ */
