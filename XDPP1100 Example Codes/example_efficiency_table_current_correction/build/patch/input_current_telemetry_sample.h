/*
** InputCurrent_telemetry_sample.h
** ============================================================================
** Copyright (C) 2020 Infineon Technologies. All rights reserved.
**               Infineon Technologies, PSS
** ============================================================================
**
** ============================================================================
** This document contains proprietary information. Passing on and
** copying of this document, and communication of its contents is not
** permitted without prior written authorisation.
** ============================================================================
**
** Created on:  2020-01-10
*/

#ifndef SRC_USER_APP_INPUT_CURRENT_TELEMETRY_SAMPLE_H_
#define SRC_USER_APP_INPUT_CURRENT_TELEMETRY_SAMPLE_H_

/* Compiler configurations first */
#include "fw_config.h"           /* Essential fw-wide configuration for e.g. buffer size #defines */
#include "patch_run.h"          /* checking for function patch points */
#include "environment.h"         /* STATIC, INLINE */
#include "shasta.h"
#include "system_shasta.h"

/* Always compare to the associated interface */
#include "telemetry_drv.h"
#include "telemetry_api.h"

#include "shasta_hal_telem.h"
#include "shasta_hal_telem_common.h"
#include "shasta_hal_fan.h"
#include "shasta_hal_tsen.h"

/* Standard library */
#include <stdint.h>              /* uint*_t */
#include "fw_bool.h"             /* boolean type */

#include "pmbus_mfr_autogen.h"

void patch_Telemetry_Sample(void);

#endif /* SRC_USER_APP_INPUT_CURRENT_TELEMETRY_SAMPLE_H_ */
