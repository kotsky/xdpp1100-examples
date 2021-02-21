/*
 * user_app.h
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

#ifndef COMMON_MODULES_USER_APP_USER_APP_H_
#define COMMON_MODULES_USER_APP_USER_APP_H_

#include "uart_drv.h"

/* iout scale Example Modification Start */
#include "pmbus_api.h"
#include "iout_range_telemetry_sample.h"
#include "iout_range_pmbus_mfr_handler.h"
/* iout scale Example Modification End */

#define N_ROWS   (128)
uint8_t  src_buf[N_ROWS];
uint8_t  dest_buf[N_ROWS];
ARM_DRIVER_USART * UARTdrv;

/* iout scale Example Modification Start */
void patch_pmbus_mfr_autogen_iout_range(void);
/* iout scale Example Modification End */

void user_drv_init(void);

#endif /* COMMON_MODULES_USER_APP_USER_APP_H_ */
