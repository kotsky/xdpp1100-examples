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

void Telemetry_IRQ(PMBUS_PAGE_t loop);
void Telemetry_IRQ_VIN_HANDLE(Telemetry_IRQ_TYPE_t Telemetry_type);
void custom_frequency_update(uint8_t loop, uint16_t frequency, int8_t frequency_exponent);

#endif
