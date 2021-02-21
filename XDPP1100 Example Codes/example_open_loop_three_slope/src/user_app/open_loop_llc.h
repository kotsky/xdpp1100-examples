/*
 * open_loop_llc.h
/* ============================================================================
** Copyright (C) 2020 Infineon. All rights reserved.
**               Infineon Technologies, PSS SYS / DES
** ============================================================================
**
** ============================================================================
** This document contains proprietary information. Passing on and
** copying of this document, and communication of its contents is not
** permitted without prior written authorization.
** ============================================================================
**
** Created on:  2020-11-10
*/

/* Open Loop Soft Startup Example Modification Start */

#ifndef SRC_USER_APP_OPEN_LOOP_LLC_H_
#define SRC_USER_APP_OPEN_LOOP_LLC_H_

#define SOFTSTART_MAX_STAGE 3

// Refer to doxy/Open_Loop_Softstart_Calculation.xlsx for detailed information
#define NUM_FORMAT_DIFF_RATIO_SCALE 5
#define NUM_FORMAT_DIFF_RATIO 41

void update_switching_period(PMBUS_PAGE_t loop, uint16_t period);
void update_force_duty(PMBUS_PAGE_t loop, uint8_t duty);

void open_loop_llc_soft_start_enable(PMBUS_PAGE_t loop);
void open_loop_llc_soft_start_disable(PMBUS_PAGE_t loop);
void open_loop_llc_soft_start_irq_handler(PMBUS_PAGE_t loop);


#endif /* SRC_USER_APP_OPEN_LOOP_LLC_H_ */

/* Open Loop Soft Startup Example Modification End */
