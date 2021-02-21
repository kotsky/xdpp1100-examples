/*
 * periodic_functions.h
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

#ifndef SRC_USER_APP_PERIODIC_FUNCTIONS_H_
#define SRC_USER_APP_PERIODIC_FUNCTIONS_H_
//
#define frequency_dither
#define ramp_switching_frequency_pcmc_startup

#ifdef frequency_dither
void frequency_dither_enable(PMBUS_PAGE_t loop);
void frequency_dither_disable(PMBUS_PAGE_t loop);
void frequency_dither_irq_callback(PMBUS_PAGE_t loop);
#endif
#ifdef ramp_switching_frequency_pcmc_startup
void ramp_switching_frequency_pcmc_startup_enable(PMBUS_PAGE_t loop);
void ramp_switching_frequency_pcmc_startup_disable(PMBUS_PAGE_t loop);
void ramp_switching_frequency_pcmc_startup_irq_handle(PMBUS_PAGE_t loop);
#endif

#endif /* SRC_USER_APP_PERIODIC_FUNCTIONS_H_ */
