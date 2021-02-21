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

#ifndef ADD_ON_FEATURES_H_
#define ADD_ON_FEATURES_H_

#include "regulation_drv.h"

void add_on_features_init (void);

// ADD-ON Features:
// add your features.

uint32_t input_current_estimation(int8_t vin_read_exp, int8_t iin_read_exp, int8_t power_read_exp, uint32_t vin, uint32_t pout);
void patch_Telemetry_Sample(void);

#endif
