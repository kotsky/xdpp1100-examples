/*
** InputCurrent_correction.h
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

#ifndef SRC_USER_APP_INPUT_CURRENT_CORRECTION_H_
#define SRC_USER_APP_INPUT_CURRENT_CORRECTION_H_

#include "driver_common.h"
#include "telemetry_api.h"
#include "pmbus_api.h"
#include "shasta_hal_telem.h"
#include "shasta_hal_fault.h"

uint16_t calculate_i(uint32_t input_voltage);
uint16_t calculate_j(uint32_t output_power);

uint16_t InputCurrent_correction(uint32_t output_power, int8_t power_read_exp, uint32_t input_current, int8_t iin_read_exp, int8_t loop );

#endif /* SRC_USER_APP_INPUT_CURRENT_CORRECTION_H_ */
