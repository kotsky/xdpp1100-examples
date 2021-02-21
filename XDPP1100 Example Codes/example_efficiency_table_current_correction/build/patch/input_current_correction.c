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

#include "input_current_correction.h"

#include "efficiency_table.h"
#include "shasta_hal_telem.h"
#include "shasta_hal_fault.h"
#include "pmbus_mfr_autogen.h"

/**
 * Function to approximate input voltage value for the correction_table/efficiency_table LUT
 * @param input_voltage value of the TLM_VIN_LPF
 */
uint16_t calculate_i(uint32_t input_voltage)
{
	for (uint8_t i = 0; i < VIN_MAX_IDX; i++)
	{
		if(input_voltage < Vin_table[i]) {
			return i;
			break;
		}
	}
}

/**
 * Function to approximate output power value for the correction_table/efficiency_table LUT
 * @param output_power value of Pout
 */
uint16_t calculate_j(uint32_t output_power)
{
	for (uint8_t j = 0; j < POUT_MAX_IDX; j++)
	{
		if(output_power <= Pout_table[j]) {
			return j;
			break;
		}
	}
}

/**
 * Function to implement and combine both Efficiency LUT and Input Current Correction LUT.
 * @param output_power value of POUT_TELEM
 * @param power_read_exp exponents of Pout
 * @param input_current value of IIN_TELEM
 * @param iin_read_exp exponents of Iin
 * @param loop selects the input_current_correction block to operate on
 */
uint16_t input_current_correction(uint32_t output_power, int8_t power_read_exp, uint32_t input_current, int8_t iin_read_exp, int8_t loop )
{
	uint32_t pout = SHIFT_EXPONENT_UNSIGNED( output_power , power_read_exp );		// to get integer (uX.0 format) real value of Output Power

	uint32_t vin_read = (uint32_t)TELEM_TLM_VIN_LPF__GET((telem_idx_t)loop);		// to get Input Voltage in u7.4 format
	vin_read = vin_read >> 4; 														// to get Input Voltage in u7.0 format

	uint16_t i = calculate_i(vin_read);		// condition searching
	uint16_t j = calculate_j(pout);

	uint16_t correction = correction_table[i][j];		// U1.9 format
	int8_t correction_exp = -9;

	uint16_t iin_corr = input_current + SHIFT_EXPONENT_UNSIGNED( input_current * correction, correction_exp ); 		// InputCurrent = InputCurrent * ( 1 + correction )

	//-----------------TO PMBUS MRF (0xB1)----------
	uint8_t efficiency = efficiency_table[i][j];		// U0.8 format
	PMBUS_Set_Command_Byte((PMBUS_PAGE_W_BROADCAST_t) loop, PMBUS_CMDCODE_MFR_ESTIMATE_EFFICIENCY, efficiency);		// set value of efficiency to MFR_ESTIMATE_EFFICIENCY
	//-----------------TO PMBUS MRF----------

	if (iin_corr>0x3FF) iin_corr = 0x3FF;

	return iin_corr; 	// max absolute value = 1023
}

