/*
 * regulation_state_machine_callbacks.h
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


#ifndef COMMON_MODULES_REGULATION_REGULATION_STATE_MACHINE_CALLBACKS_H_
#define COMMON_MODULES_REGULATION_REGULATION_STATE_MACHINE_CALLBACKS_H_

#include "faults_api.h"

#define VOUT_Thresh_Count_Max 3 //Number of thresholds used (Thresh0..2)

/**
 * Driver global variable structure for easy debug
 */
//extern REGULATION_MODULE_t REGULATION_APP;
/**
 * Local queue for priority reordering
 */
//extern regulation_inter_thread_message_t REGULATION_APP_QUEUE[REGULATION_QUEUE_LENGTH];

typedef struct {
	uint32_t vout[NUM_LOOPS];	//!< current telemetry value for output voltage of each loop
	uint32_t iout[NUM_LOOPS];	//!< current telemetry value for output current of each loop
	uint32_t iin[NUM_LOOPS];	//!< current telemetry value for input current of each loop
	uint32_t vin[NUM_LOOPS];	//!< current telemetry value for input voltage of each loop
	uint32_t pout[NUM_LOOPS];	//!< current telemetry value for input voltage of each loop
	uint32_t pin[NUM_LOOPS];	//!< current telemetry value for input voltage of each loop
	uint32_t fsw[NUM_LOOPS];	//!< current telemetry value for input voltage of each loop
	uint32_t duty[NUM_LOOPS];	//!< current telemetry value for input voltage of each loop
	uint32_t prebias_voltage[NUM_LOOPS];	//!< current telemetry value for output voltage at startup
	uint32_t leakage_current[NUM_LOOPS];	//!< current telemetry value for output current at startup
	uint32_t cout[NUM_LOOPS];	//!< current telemetry value for output capacitance of each loop
	uint32_t lout[NUM_LOOPS];	//!< current telemetry value for output inductance of each loop
	uint32_t temperature[3];  	//!< current telemetry value for temperature, index: tempa = 0, tempb = 1, tempi = 2

	uint32_t period_max[NUM_LOOPS];	//!< period used by frequency jitter feature
	uint32_t period_min[NUM_LOOPS];	//!< period used by frequency jitter feature
	uint32_t counter[NUM_LOOPS];	//!< counter used by frequency jitter feature
	uint8_t control[NUM_LOOPS];	//!< control used by frequency jitter feature
	uint8_t  up0_down1[NUM_LOOPS];	//!< flag for ramp up or down used by frequency jitter feature

	uint32_t calculated_droop;
	uint32_t current_droop;
	uint32_t enable_read_iout_adc_codes[NUM_LOOPS];
	uint8_t enable_added_droop;
	uint8_t remove_added_droop_counter;

	uint8_t  VOUT_Thresh_Count;
	int8_t   VOUT_Thresh_Exponent;
	uint32_t VOUT_Thresh[VOUT_Thresh_Count_Max];

	uint32_t otp_osc_trim;
	uint8_t otp_adc_offset[NUM_LOOPS];
	uint8_t password_locked;
	int8_t   VIN_Thresh_Exponent;
	uint32_t VIN_Thresh;
	uint32_t hash;

	FAULT_TYPE_t last_high_priority_fault[NUM_LOOPS]; //for patch

	uint32_t fsw_initial_period[NUM_LOOPS]; //!< startup value of period used by ramp_switching_frequency_pcmc_startup feature

	uint8_t  board_trim_loaded;	//!< flag for board trim execution perfromed


} USER_DATA_t;

extern USER_DATA_t user_data;

void regulation_sm_callbacks_init(void);
void TON_DELAY_ENABLE(PMBUS_PAGE_t loop);
void TON_RISE_VID_REACHED(PMBUS_PAGE_t loop);
void TON_RISE_ENABLE(PMBUS_PAGE_t loop);
void AT_TARGET_ENABLE(PMBUS_PAGE_t loop);
void AT_SHUTDOWN(PMBUS_PAGE_t loop);
void Telemetry_IRQ_VIN_HANDLE(Telemetry_IRQ_TYPE_t telem_type);
void USER_Log_Error(uint32_t program_counter, PMBUS_CML_STATUS_e cml_status);

#endif /* COMMON_MODULES_REGULATION_REGULATION_STATE_MACHINE_CALLBACKS_H_ */
