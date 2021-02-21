/*
 * adaptive_deadtime_adjustment.c
 *
 *  Created on: 20 Feb 2020
 *      Author: halimand
 */


#include "adaptive_deadtime_adjustment.h"

extern USER_DATA_t user_data;


/**
 * Function to adjust the deadtime settings according to the threshold level
 * Regulation_set_regulation_event_cb(REGULATION_STATE_AT_TARGET_VID, REGULATION_CONTROLS_TELEMETRY_UPDATED, adaptive_deadtime_adjustment);
 * @param loop select the pmbus page to operate on
 */
void adaptive_deadtime_adjustment(PMBUS_PAGE_t loop)
{
	int16_t exponent, mantissa;

	// 1. GET ALL NECESSARY THRESHOLD AND HYSTERESIS VALUE FROM PMBUS MFR COMMANDS
	exponent = (int16_t)LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST));
	mantissa = (int16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_HYST));
	uint32_t hyst = (uint32_t)SHIFT_EXPONENT(mantissa, exponent);

	exponent = (int16_t)LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1));
	mantissa = (int16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_1));
	uint32_t thres_1 = (uint32_t)SHIFT_EXPONENT(mantissa, exponent);

	exponent = (int16_t)LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2));
	mantissa = (int16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_2));
	uint32_t thres_2 = (uint32_t)SHIFT_EXPONENT(mantissa, exponent);

	exponent = (int16_t)LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3));
	mantissa = (int16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIME_THRESHOLD_LEVEL_3));
	uint32_t thres_3 = (uint32_t)SHIFT_EXPONENT(mantissa, exponent);

	exponent = (int16_t)LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_IOUT_OC_FAULT_LIMIT));
	mantissa = (int16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_IOUT_OC_FAULT_LIMIT));
	uint32_t iout_max = (uint32_t)SHIFT_EXPONENT(mantissa, exponent);

	// 2. CHECK WHETHER THRESHOLD AND HYSTERESIS MAKE SENSE
	if ((iout_max > thres_3) && (thres_3 > thres_2) && (thres_2 > thres_1))
	{

		// 3. READ OUTPUT CURRENT IOUT
		exponent = (int16_t)LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_READ_IOUT));
		mantissa = (int16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_READ_IOUT));
		uint32_t iout = (uint32_t)SHIFT_EXPONENT(mantissa, exponent);

		// Declare pointer to Deadtimes (PWMs values)
		uint8_t *pDeadtime = NULL; // assign to NULL first because Deadtimes might not be updated.

		// Boolean flag to allow Deadtimes update. Needed to prevent Deadtimes got updated with NULL pointer.
		boolean bUpdateDeadtime = 0;

		// 4. ASSIGN PWM DEADTIME ACCORDINGLY.
		if (iout < iout_max && iout >= thres_3)	// 	Region D
		{
			user_data.deadtime_curr_region = 3;	// Region D

			// Iout in Region D
			if (iout >= (thres_3 + hyst))
			{
				pDeadtime = PMBUS_GET_DATA_ARRAY_POINTER(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_3);
				bUpdateDeadtime = 1;
			}

			// Iout in hyst region D
			else
			{
				switch(user_data.deadtime_prev_region)
				{
					case 3: // If prev Region was D but curr Region is D, do nothing
						break;
					case 2: // If prev Region was C but curr Region is D, do nothing
						break;
					case 1: // If prev Region was B but curr Region is D, update Deadtimes
						pDeadtime = PMBUS_GET_DATA_ARRAY_POINTER(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_3);
						bUpdateDeadtime = 1;
						break;
					case 0: // If prev Region was A but curr Region is D, update Deadtimes
						pDeadtime = PMBUS_GET_DATA_ARRAY_POINTER(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_3);
						bUpdateDeadtime = 1;
						break;
					default:
						break;
				}
			}
		}

		else if (iout < thres_3 && iout >= thres_2)	// Region C
		{
			user_data.deadtime_curr_region = 2;	// Region C

			// Iout in Region C
			if (iout >= (thres_2 + hyst))
			{
				pDeadtime = PMBUS_GET_DATA_ARRAY_POINTER(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_2);
				bUpdateDeadtime = 1;
			}

			// Iout in hyst region C
			else
			{
				switch(user_data.deadtime_prev_region)
				{
					case 3: // If prev Region was D but curr Region is C, update Deadtimes
						pDeadtime = PMBUS_GET_DATA_ARRAY_POINTER(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_2);
						bUpdateDeadtime = 1;
						break;
					case 2:	// If prev Region was C but curr Region is C, do nothing
						break;
					case 1: // If prev Region was B but curr Region is C, do nothing
						break;
					case 0: // If prev Region was A but curr Region is C, update Deadtimes
						pDeadtime = PMBUS_GET_DATA_ARRAY_POINTER(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_2);
						bUpdateDeadtime = 1;
						break;
					default:
						break;
				}
			}
		}

		else if (iout < thres_2 && iout >= thres_1)	// Region B
		{
			user_data.deadtime_curr_region = 1;	// Region B

			// Iout in idem region B
			if (iout >= (thres_1 + hyst))
			{
				pDeadtime = PMBUS_GET_DATA_ARRAY_POINTER(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_1);
				bUpdateDeadtime = 1;
			}

			// Iout in hyst region B
			else
			{
				switch(user_data.deadtime_prev_region)
				{
					case 3: // If prev Region was D but curr Region is B, update Deadtimes
						pDeadtime = PMBUS_GET_DATA_ARRAY_POINTER(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_1);
						bUpdateDeadtime = 1;
						break;
					case 2: // If prev Region was C but curr Region is B, update Deadtimes
						pDeadtime = PMBUS_GET_DATA_ARRAY_POINTER(loop, PMBUS_CMDCODE_MFR_ADAPTIVE_DEADTIMES_REGION_1);
						bUpdateDeadtime = 1;
						break;
					case 1: // If prev Region was B but curr Region is B, do nothing
						break;
					case 0: // If prev Region was A but curr Region is B, do nothing
						break;
					default:
						break;
				}
			}
		}

		else if (iout < thres_1)	// Region A
		{

			user_data.deadtime_curr_region = 0;	// Region A

			pDeadtime = PMBUS_GET_DATA_ARRAY_POINTER(loop, PMBUS_CMDCODE_PWM_DEADTIME);
			bUpdateDeadtime = 1;
		}
		else
		{
			// if-else will not go in here. put this for MISRA-C compliance
			// https://stackoverflow.com/questions/35053371/what-is-the-benefit-of-terminating-if-else-if-constructs-with-an-else-clause

		}

		// update Prev region
		user_data.deadtime_prev_region = user_data.deadtime_curr_region;

		// 5. UPDATE PWM_DEADTIME
		// each byte pair in PMBUS_CMDCODE_PWM_DEADTIME is decoded as {pwmx_df[7:0], pwmx_dr[7:0]} for each phase
		if (bUpdateDeadtime)
		{
			uint8_t pwm = 0;

			for (uint8_t i = 0; i < 24; i+=2)
			{
				// update pwm deadtime register ( HAL )
				if (pwm != 11U)
				{
					Regulation_PWM_Deadtime_Set(pwm, pDeadtime[i+1], pDeadtime[i]);
				}
				else
				{
						PWM_PWM12_DEADTIME__SET(PWM_PWM12_DEADTIME__GET());  // just write back same value as before
				}
				pwm++;
			}
		}
	}
}


/**
 * Function to reinitialize the deadtime settings before Shasta gets back to regulation control (e.g. off, fault)
 * Regulation_set_regulation_event_cb(REGULATION_STATE_TON_DELAY, REGULATION_CONTROLS_ENABLE, initialize_deadtime_beginning);
 * @param loop select the pmbus page to operate on
 */
void adaptive_deadtime_init(PMBUS_PAGE_t loop)
{
	loop = PMBUS_PAGE_0;

	uint8_t *pDeadtime = PMBUS_GET_DATA_ARRAY_POINTER(loop, PMBUS_CMDCODE_PWM_DEADTIME);

	// set default pwm deadtimes
	uint8_t pwm = 0;

	for (uint8_t i = 0; i < 24; i+=2)
	{
		// update pwm deadtime register ( HAL )
		Regulation_PWM_Deadtime_Set(pwm, pDeadtime[i+1], pDeadtime[i]);
		pwm++;
	}

	// initialize deadtime regions
	user_data.deadtime_prev_region = 0;
	user_data.deadtime_curr_region = 0;
}
