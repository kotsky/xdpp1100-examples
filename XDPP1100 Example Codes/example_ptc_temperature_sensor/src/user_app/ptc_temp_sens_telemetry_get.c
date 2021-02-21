/*
 * patch_Telemetry_get_adc_code.c
 *
 *  Created on: 3 Sep 2019
 *      Author: halimand
 */

#include "regulation_api.h"
#include "pmbus_api.h"
#include "ptc_temp_sens_telemetry_get.h"
#include "pmbus_mfr_autogen.h"

/**
 * Gets the adc code equivalent of a given temperature in C, modification for ptc_temperature_sensor example
 * range of table is -40C to 150C
 * adc codes distributed across the voltage range up to 511
 * @param temp temperature in C
 * @return adc codes 0-511
 */
uint16_t patch_Telemetry_get_adc_code(int16_t temp)
{
	for (uint16_t i = 0; i< 512; i++)
	{
		if (ntc_temp[i] >= temp)
		{
			return (i);
		}
	}
	return (511);
}

/**
 * Generic function to get telemetry values, modification for ptc_temperature_sensor example
 * @param loop Selects the loop to operate on.  Valid range of 0 or 1.
 * @return vout in vout_exp format unsigned
 */
int32_t patch_Telemetry_get(PMBUS_PAGE_t loop, TELEMETRY_TYPE_t telem_type)
{

	int32_t telem;
    uint32_t telem_unsigned = 0;
	int32_t gain;
	int32_t offset;
	uint32_t vout_scale;
	int32_t Telemetry_exponent;
	int32_t read_exp;

	switch (telem_type)
	{
		case VOUT_TELEM:
			telem = (int32_t)TELEM_TLM_VOUT_FSW__GET((telem_idx_t)loop);  // lsb = 1.25mv u12.0
			//debug[0] = 0xAA;
			Telemetry_exponent = Telemetry_VOUT_EXP;
			read_exp = PMBUS_Q_EXP;
			break;
		case IOUT_TELEM :
			telem = (int32_t)TWOS_UNCOMPLEMENT(13, (TELEM_TLM_IOUT_FSW__GET((telem_idx_t)loop)));  // S9.4, LSB 62.5mA
			Telemetry_exponent = Telemetry_IOUT_EXP;
			read_exp = TWOS_UNCOMPLEMENT(4, Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)TELEMETRY_CONFIG_READ_IOUT_EXP));
			break;
		case VIN_TELEM :
			telem = (int32_t)TELEM_TLM_VIN_LPF__GET((telem_idx_t)loop); //u7.4
			Telemetry_exponent = Telemetry_VIN_EXP;
			read_exp = TWOS_UNCOMPLEMENT(4, Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)TELEMETRY_CONFIG_READ_VIN_EXP));
			break;
		case IIN_TELEM :
			telem = (int32_t)TELEM_TLM_IIN_LPF__GET((telem_idx_t)loop);
			Telemetry_exponent = Telemetry_IIN_EXP;
			read_exp = TWOS_UNCOMPLEMENT(4, Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)TELEMETRY_CONFIG_READ_IIN_EXP));
			break;
		case ATSEN_TELEM :
			telem = (int32_t)TLMCOM_TLM_ATSEN_LPF__GET();
			Telemetry_exponent = Telemetry_TEMP_EXP;
			read_exp = Telemetry_TEMP_EXP;
			break;
		case BTSEN_TELEM :
			telem = (int32_t)TLMCOM_TLM_BTSEN_LPF__GET();
			Telemetry_exponent = Telemetry_TEMP_EXP;
			read_exp = Telemetry_TEMP_EXP;
			break;
		case ITSEN_TELEM :
			telem = (int32_t)TLMCOM_TLM_ITSEN_LPF__GET();
			Telemetry_exponent = Telemetry_TEMP_EXP;
			read_exp = Telemetry_TEMP_EXP;
			break;
		case XADDR1_TELEM :
			telem = (int32_t)TLMCOM_TLM_XADDR1_LPF__GET();
			Telemetry_exponent = Telemetry_TEMP_EXP;
			read_exp = Telemetry_TEMP_EXP;
			break;
		case XADDR2_TELEM :
			telem = (int32_t)TLMCOM_TLM_XADDR2_LPF__GET();
			Telemetry_exponent = Telemetry_TEMP_EXP;
			read_exp = Telemetry_TEMP_EXP;
			break;
		case DUTY_TELEM:
			telem = (int32_t)TELEM_TLM_DUTY_FSW__GET((telem_idx_t)loop);  // u0.16
			telem = telem*100;  // convert to percent in u0.16 format
			Telemetry_exponent = Telemetry_DUTY_EXP;
			read_exp = TWOS_UNCOMPLEMENT(4, Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)TELEMETRY_CONFIG_READ_DUTY_EXP));
			break;
		case FSW_TELEM :
			telem = (int32_t)TELEM_TLM_FREQ__GET((telem_idx_t)loop);  // u11.0 format 1khz lsb
			Telemetry_exponent = Telemetry_FSW_EXP;
			read_exp = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_FREQUENCY_SWITCH));
			break;
		default:
			telem = 0;  // u11.0 format 1khz lsb
			read_exp = 0;
			Telemetry_exponent = 0;
			PMBUS_Log_Error(TELEMETRY, PROGRAM_COUNTER, PMBUS_STATUS_CML_PROCESSOR_FAULT);
			break;
	}


	if (telem_type == VOUT_TELEM)
	{
		telem_unsigned = SHIFT_EXPONENT_UNSIGNED((uint32_t)telem, Telemetry_exponent - read_exp); // convert vout fsw to Q=-16 (32 bit number)
		// see vout_target_setpoint_computations.xlsx for equations
		vout_scale = (PMBUS_Get_Command_Word(loop, PMBUS_CMDCODE_VOUT_SCALE_LOOP));  // get scale in Q=-16 (16bit number)
		if (vout_scale == 0) vout_scale = 1;  // avoid divide by zero
		telem_unsigned = DIVIDE_WITH_ROUNDING((uint32_t)telem_unsigned , ((uint32_t)DAC_STEP_SIZE_VOLTS_TO_0_156MV));  // convert vout_fsw to volts Q=-16
		telem_unsigned = SHIFT_EXPONENT_UNSIGNED(telem_unsigned, -read_exp-3);  // shift back up to Q=-13 to divide
		telem_unsigned = DIVIDE_WITH_ROUNDING(telem_unsigned , vout_scale);  // divide by vout_scale to get scaled volts
		telem_unsigned = SHIFT_EXPONENT_UNSIGNED(telem_unsigned, 3);  // back to Q=-16
	}

	else
	{
		telem = SHIFT_EXPONENT(telem, Telemetry_exponent - read_exp); // convert vout fsw to Q=-16 (32 bit number)
	}

	if ((uint32_t)telem_type < (uint32_t)ITSEN_TELEM) //Itsen, Duty and Freq do not have offset and gain
	{
		// grab the s-5.9 or format gain from telem config convert to int32
		// 1 + (gain_base[s4.4] << 5)[s4.9] + gain[s-5.9]
		/*lint -e701 */
		gain = 512 + (TWOS_UNCOMPLEMENT(8, Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)((uint32_t)TELEMETRY_CONFIG_VOUT_GAIN_BASE + (8*(uint32_t)telem_type)))) << 5);
		gain += TWOS_UNCOMPLEMENT(4, Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)((uint32_t)TELEMETRY_CONFIG_VOUT_GAIN + (4*(uint32_t)telem_type))));

		// offset in telem_type format already covert to int32
		offset = TWOS_UNCOMPLEMENT(8, Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)((uint32_t)TELEMETRY_CONFIG_VOUT_OFFSET + (8*(uint32_t)telem_type))));

		if (telem_type == VOUT_TELEM)
		{
			offset = SHIFT_EXPONENT(offset, PMBUS_Get_Vout_Mode_Exponent((PMBUS_PAGE_t)loop) - read_exp); // convert to READ_Exponent
		}
	}
	else {
		gain = SHIFT_EXPONENT(1, -Telemetry_GAIN_EXP);
		offset = 0;
	}
	// multiply the gain by the telem value and shift down by Telemetry_GAIN_EXP to
	// get read_exp Q format number post multiply
	if (telem_type == VOUT_TELEM)
	{
		telem_unsigned = telem_unsigned*(uint32_t)gain;  // multiply by gain ~512 in Q0 format
		telem_unsigned = SHIFT_EXPONENT_UNSIGNED(telem_unsigned, Telemetry_GAIN_EXP);  // shift down by 9
		telem = offset + (int32_t)telem_unsigned;  // add in the offset
	}
	else
	{
		telem = SHIFT_EXPONENT(telem*gain, Telemetry_GAIN_EXP);
		telem = offset + telem;  // add in the offset
	}

	/*lint -e845 */
	if ((telem_type ==  ATSEN_TELEM) || (telem_type == BTSEN_TELEM))
	{
		if (ntc_temp != NULL)
		{
			if (telem<0) telem = 0;
			if (telem>511) telem = 511;
			telem = ntc_temp[telem];
		}
		else
		{
			PMBUS_Log_Error(TELEMETRY, PROGRAM_COUNTER, PMBUS_STATUS_CML_PROCESSOR_FAULT);
		}
	}

	return telem;
}
