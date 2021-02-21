/*
 * pmbus_mfr_specific_handlers.c
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
#include "shasta_hal_scu.h"
#include "shasta_hal_cgu.h"
#include "shasta_hal_rgu.h"
#include "shasta_hal_telem.h"
#include "shasta_hal_fan.h"
#include "shasta_hal_trim.h"
#include "shasta_hal_vsen.h"
#include "regulation_api.h"
#include "faults_api.h"
#include "faults_drv.h"
#include "regulation_drv.h"
#include "telemetry_drv.h"
#include "pmbus_drv.h"
#include "driver_common.h"
#include "log_app.h"
#include "regulation_state_machine_callbacks.h"
#include "add_on_features.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "uart_drv.h"
#include "user_app.h"
/*  Hallo Welt Example modification Start*/
#include "hallo_welt.h"
/*  Hallo Welt Example modification End*/

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
*/

/**
 * Added Example function for Hallo Welt
 * This is an example of how to add new firmware commands to MFR_FIRMWARE_COMMAND PMBus command
 * Hallo Welt send handler.
 * @param page Selects the PMBus page to operate on.
 * @param direction Can either be PMBUS_WRITE or PMBUS_READ types
 */
void PMBUS_HANDLE_MFR_Hallo_Welt(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	uint8_t common;
	if ((direction == PMBUS_WRITE)||(direction == OTP_RESTORE))
	{
		// Get PMBus MFR DEADTIME value and put in user_data "common" for storing
		common = PMBUS_Get_Command_Byte(page, PMBUS_CMDCODE_MFR_Hallo_Welt);

		if (common == 0xff)// if command 0xff is received, initialize uart channel and send string
		{
			hallo_welt();
		}
	}
}
