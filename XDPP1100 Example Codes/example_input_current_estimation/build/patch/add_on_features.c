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

/* Standard library */
#include "telemetry_api.h"
#include "regulation_api.h"
#include "regulation_drv.h"
#include "faults_api.h"
#include "faults_drv.h"
#include "shasta_hal_tsen.h"
#include "shasta_hal_pwm.h"
#include "shasta_hal_pid.h"
#include "shasta_hal_analog.h"
#include "shasta_hal_common.h"
#include "shasta_hal_vcontrol.h"
#include "shasta_hal_isen.h"
#include "log_app.h"             /* Logging of errors */
#include <string.h>             /* memset */
#include "patch_rom_table.h"
#include "string.h"
#include "add_on_features.h"
#include "shasta_hal_tstctrl.h"  	// ate test state
#include "mmu_drv.h"                /* MMU_Initialization */
#include "driver_common.h"
#include "shasta_hal_fault_common.h"
#include "shasta_hal_fault.h"
#include "shasta_hal_vcontrol.h"
#include "pmbus_autogen.h"      // PMBUS_PAGE_t
#include "pmbus_mfr_autogen.h"

void add_on_features_init (void)
{
	uint8_t test1 = 0;
}

/**
 * The function below performs manual input current calculation
 * according to the formula: iin = pout / (vin * efficiency), where
 * vin - input voltage
 * iin- input current
 * pout - output power
 * @param power_read_exp exponents of Pout
 * @param input_current value of IIN_TELEM
 * @param iin_read_exp exponents of Iin
 * @param loop selects the input_current_correction block to operate on
 */

uint32_t input_current_correction(int8_t vin_read_exp, int8_t iin_read_exp, int8_t power_read_exp, uint32_t vin, uint32_t pout)
{
	// For an instance, we might use an efficiency correction to get accurate input current estimation
	// Refer to example_efficiency_table_current_correction.zip and
	// "Efficiency Look-Up Table and Input Current Correction Look-Up Table" in "XDPP1100 Firmware Examples.pdf"
	uint8_t efficiency = 0xEA;		// in U0.8 format 0xEA or 234 => efficiency = 0.9140625

	uint32_t prod_vin_eff;
	prod_vin_eff = vin*efficiency;	//u7.vin_exp*u0.8 = u7.(8+vin_exp)
	prod_vin_eff = SHIFT_EXPONENT_UNSIGNED( prod_vin_eff  , vin_read_exp );   // u7.8

	uint32_t one_div_prod_vin_eff;

	one_div_prod_vin_eff = (1U<<24) / (prod_vin_eff);  //24 also includes the 2^8 accounted form efficiency, so this will be X.16

	uint32_t prod_pout_one_div_vin_eff;

	uint16_t reqrd_shift = 16;
	uint16_t iin_exp_shift = 0;

	if(iin_read_exp > 0x80)
	{
		iin_exp_shift = (0x100 - iin_read_exp); // 128 is a dummy number to avoid implementing this for positive exp
		reqrd_shift = (reqrd_shift - iin_exp_shift);
	}
	else
	{
		iin_exp_shift = iin_read_exp; // 128 is a dummy number to avoid implementing this for positive exp
		reqrd_shift = reqrd_shift + iin_exp_shift;
	}
	prod_pout_one_div_vin_eff = SHIFT_EXPONENT_UNSIGNED(one_div_prod_vin_eff*pout, power_read_exp);
	prod_pout_one_div_vin_eff = prod_pout_one_div_vin_eff >> reqrd_shift;   //for Iin exp = -2, must be right shifted by 14, shift based on exp selected

	uint32_t iin_corr = prod_pout_one_div_vin_eff;

	if (iin_corr>0x3FF) iin_corr = 0x3FF;

	return iin_corr; 	// max absolute value = 1023

}

void patch_Telemetry_Sample(void)
{
	uint8_t loop;
	uint32_t vout, vin, iin, pin, pout, duty, fsw;

	int8_t vout_read_exp[NUM_LOOPS];
	int8_t vin_read_exp[NUM_LOOPS];
	int8_t iout_read_exp[NUM_LOOPS];
	int8_t iin_read_exp[NUM_LOOPS];
	int8_t duty_read_exp[NUM_LOOPS];
	int8_t power_read_exp[NUM_LOOPS];
	int8_t fan_read_exp[NUM_LOOPS];
	int8_t fsw_read_exp[NUM_LOOPS];

	int32_t iout;
	int32_t tempa, tempb, tempi;
	int32_t temp_1, temp_2;
	// update the telemetry data at the bandwidth period:

	//for (uint8_t loop=0;loop<(uint8_t)NUM_LOOPS;loop++)
	for(loop=0; loop<(uint8_t)NUM_LOOPS; loop++)  // update for the number of loops in the system
	{
	//GET_EXPONENTS
		//int32_t vout_exp = PMBUS_Q_EXP;
		vout_read_exp[loop] = (int8_t)PMBUS_Get_Vout_Mode_Exponent((PMBUS_PAGE_t)loop);
		fsw_read_exp[loop]  = (int8_t)LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_FREQUENCY_SWITCH));
		vin_read_exp[loop]  = (int8_t)TWOS_UNCOMPLEMENT(4, Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)TELEMETRY_CONFIG_READ_VIN_EXP));
		iout_read_exp[loop] = (int8_t)TWOS_UNCOMPLEMENT(4, Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)TELEMETRY_CONFIG_READ_IOUT_EXP));
		iin_read_exp[loop]  = (int8_t)TWOS_UNCOMPLEMENT(4, Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)TELEMETRY_CONFIG_READ_IIN_EXP));
		duty_read_exp[loop] = (int8_t)TWOS_UNCOMPLEMENT(4, Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)TELEMETRY_CONFIG_READ_DUTY_EXP));
		power_read_exp[loop]= (int8_t)TWOS_UNCOMPLEMENT(3, Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)TELEMETRY_CONFIG_READ_POWER_EXP));
		fan_read_exp[loop]  = (int8_t)TWOS_UNCOMPLEMENT(4, Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)PMBUS_PAGE_0, (TELEMETRY_CONFIG)TELEMETRY_CONFIG_READ_FAN_EXP));

	//VOUT_TELEM
		vout = (uint32_t)Telemetry_get((PMBUS_PAGE_t)loop, VOUT_TELEM);
		vout = (uint32_t)SHIFT_EXPONENT((int32_t)vout,  PMBUS_Q_EXP - vout_read_exp[loop]);  // convert to vout_mode format
		if (vout>0xFFFF) vout = 0xFFFF;
		TELEM_DATA.vout[loop] = vout;
	//IOUT_TELEM
		iout = Telemetry_get((PMBUS_PAGE_t)loop, IOUT_TELEM);
		if (iout>1023) iout = 1023;
		if (iout<-1023) iout = -1023;
		TELEM_DATA.iout[loop] = iout;
	//VIN_TELEM
		vin = (uint32_t)Telemetry_get((PMBUS_PAGE_t)loop, VIN_TELEM);
		if (vin>0x3FF) vin = 0x3FF;
		TELEM_DATA.vin[loop] = vin;

	//DUTY_TELEM
		duty = (uint32_t)Telemetry_get((PMBUS_PAGE_t)loop, DUTY_TELEM);
		if (duty>0x3FF) duty = 0x3FF;
		TELEM_DATA.duty[loop] = duty;
	//FSW_TELEM
		fsw = (uint32_t)Telemetry_get((PMBUS_PAGE_t)loop, FSW_TELEM);
		if (fsw>0x3FF)  fsw = 0x3FF;
		TELEM_DATA.fsw[loop] = fsw;
	//POUT_TELEM
		pout = (uint32_t)Telemetry_get_power(vout, vout_read_exp[loop], iout, iout_read_exp[loop], power_read_exp[loop]); //in read_power_exp
		if (pout>0x3ff) pout=0x3ff;
		TELEM_DATA.pout[loop] = pout;

/* Input current correction Example Modification Start */
	//IIN_TELEM updated calculation
		iin = (uint32_t)Telemetry_get((PMBUS_PAGE_t)loop, IIN_TELEM);
		if (iin>0x3FF) iin = 0x3FF;
		iin = (uint32_t)input_current_correction(vin_read_exp[loop], iin_read_exp[loop], power_read_exp[loop], vin, pout);	// correction of Input Current
		TELEM_DATA.iin[loop] = iin;
	//PIN_TELEM put after IIN calculation
		pin = (uint32_t)Telemetry_get_power(vin, vin_read_exp[loop], (int32_t)iin, iin_read_exp[loop], power_read_exp[loop]);
		if (pin > 0x3ff) pin = 0x3ff;  // cap value
		TELEM_DATA.pin[loop] = pin;
/* Input current correction Example Modification End */

		if (Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)TELEMETRY_CONFIG_FW_FILTER_EN) == 1) {
			vout = (vout + (uint32_t)(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_READ_VOUT)))>>1;
			/*lint -e702 */
			iout = (iout + (LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_READ_IOUT))))>>1u;
			vin  = (vin  + (uint32_t)(LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_READ_VIN))))>>1u;
			iin  = (iin  + (uint32_t)(LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_READ_IIN))))>>1u;
			duty = (duty + (uint32_t)(LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_READ_DUTY_CYCLE))))>>1u;
			fsw  = (fsw +  (uint32_t)(LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_READ_FREQUENCY))))>>1u;
		}

		TELEMETRY_VIN_SOURCE source = Telemetry_get_vin_source((PMBUS_PAGE_t)loop);
		if ((ON_OFF_STATE.On_Off_State[loop]==0)&&
				((source == (TELEMETRY_VIN_SOURCE)TELEMETRY_VIN_SOURCE_VRECT1) || (source == (TELEMETRY_VIN_SOURCE)TELEMETRY_VIN_SOURCE_VRECT2)))
		{
			// if we have vrect sensing and not actively switching we need to set read_vin to 0v
			PMBUS_Set_Command_Word((PMBUS_PAGE_W_BROADCAST_t)loop, (uint8_t)PMBUS_CMDCODE_READ_VIN, (uint16_t)(((TWOS_COMPLEMENT (5, vin_read_exp[loop]))<<11)));
		}
		else
		{
			// otherwise we have real telemetry for vin from primary or forced values
			PMBUS_Set_Command_Word((PMBUS_PAGE_W_BROADCAST_t)loop, (uint8_t)PMBUS_CMDCODE_READ_VIN, (uint16_t)(((TWOS_COMPLEMENT (5, vin_read_exp[loop]))<<11) | (vin & 0x7ff))); // read_vin is u7.2
		}

		PMBUS_Set_Command_Word((PMBUS_PAGE_W_BROADCAST_t)loop, (uint8_t)PMBUS_CMDCODE_READ_VOUT,      (uint16_t)vout);
		PMBUS_Set_Command_Word((PMBUS_PAGE_W_BROADCAST_t)loop, (uint8_t)PMBUS_CMDCODE_READ_IOUT,      (uint16_t)( (TWOS_COMPLEMENT (5, iout_read_exp[loop] )<<11) | ((uint16_t)iout & 0x7ff))); // read_iout is s7.2
		PMBUS_Set_Command_Word((PMBUS_PAGE_W_BROADCAST_t)loop, (uint8_t)PMBUS_CMDCODE_READ_IIN,       (uint16_t)( (TWOS_COMPLEMENT (5, iin_read_exp[loop]  )<<11) | (iin  & 0x7ff))); // read_iin is u6.4
		PMBUS_Set_Command_Word((PMBUS_PAGE_W_BROADCAST_t)loop, (uint8_t)PMBUS_CMDCODE_READ_POUT,      (uint16_t)( (TWOS_COMPLEMENT (5, power_read_exp[loop])<<11) | (pout & 0x7ff))); // fixed at u10.0 format
		PMBUS_Set_Command_Word((PMBUS_PAGE_W_BROADCAST_t)loop, (uint8_t)PMBUS_CMDCODE_READ_PIN,       (uint16_t)( (TWOS_COMPLEMENT (5, power_read_exp[loop])<<11) | (pin  & 0x7ff)));
		PMBUS_Set_Command_Word((PMBUS_PAGE_W_BROADCAST_t)loop, (uint8_t)PMBUS_CMDCODE_READ_DUTY_CYCLE,(uint16_t)( (TWOS_COMPLEMENT (5, duty_read_exp[loop] )<<11) | (duty & 0x7ff)));  // u7.3 %
		PMBUS_Set_Command_Word((PMBUS_PAGE_W_BROADCAST_t)loop, (uint8_t)PMBUS_CMDCODE_READ_FREQUENCY, (uint16_t)( (TWOS_COMPLEMENT (5, fsw_read_exp[loop]  )<<11) | (fsw  & 0x7ff)));  // Return READ_FREQUENCY in FREQUENCY_SWITCH format

		//GET_POWER_Thresholds
			int32_t exponent = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_POUT_OP_WARN_LIMIT));
			int16_t mantissa = (int16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_POUT_OP_WARN_LIMIT));
			POWER_WARN_THRESH[loop].pout_op_warn_thresh = (uint16_t) SHIFT_EXPONENT(mantissa, (- power_read_exp[loop] + exponent));
			exponent = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_PIN_OP_WARN_LIMIT));
			mantissa = (int16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_PIN_OP_WARN_LIMIT));
			POWER_WARN_THRESH[loop].pin_op_warn_thresh = (uint16_t) SHIFT_EXPONENT(mantissa, (- power_read_exp[loop] + exponent));

		//POUT_OP Firmware Fault
		if (pout>POWER_WARN_THRESH[loop].pout_op_warn_thresh)
		{
			Set_Firmware_Fault((PMBUS_PAGE_t)loop, FAULT_TYPE_POUT_OP_WARN);
		}
		else
		{
			Clear_Firmware_Fault((PMBUS_PAGE_t)loop, FAULT_TYPE_POUT_OP_WARN);
		}

		//PIN_OP Firmware Fault
		if (pin>POWER_WARN_THRESH[loop].pin_op_warn_thresh)
		{
			Set_Firmware_Fault((PMBUS_PAGE_t)loop, FAULT_TYPE_PIN_OP_WARN);
		}
		else
		{
			Clear_Firmware_Fault((PMBUS_PAGE_t)loop, FAULT_TYPE_PIN_OP_WARN);
		}

	}

  //ATSEN_TELEM
	tempa = Telemetry_get(PMBUS_PAGE_0, ATSEN_TELEM);
	TELEM_DATA.temperature[0] = tempa;
  //BTSEN_TELEM
	tempb = Telemetry_get(PMBUS_PAGE_0, BTSEN_TELEM);
	TELEM_DATA.temperature[1] = tempb;
  //ITSEN_TELEM
	tempi = Telemetry_get_tempi();
	TELEM_DATA.temperature[2] = tempi;
	//tempa = Telemetry_get((PMBUS_PAGE_t)loop, ITSEN_TELEM);

	// Here we determine which READ_TEMPERATURE gets tempA, tempB, and tempI
	for(loop=0; loop<NUM_LOOPS; loop++)
	{
		switch ((PMBUS_Get_Command_Byte ((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_MFR_SELECT_TEMPERATURE_SENSOR)) & 0x7 )
		{
			case 0:
				temp_1 = tempa;
				temp_2 = tempb;
				break;
			case 1:
				temp_1 = tempa;
				temp_2 = tempi;
				break;
			case 2:
				temp_1 = tempb;
				temp_2 = tempa;
				break;
			case 3:
				temp_1 = tempb;
				temp_2 = tempi;
				break;
			case 4:
				temp_1 = tempi;
				temp_2 = tempa;
				break;
			case 5:
				temp_1 = tempi;
				temp_2 = tempb;
				break;
			default:
				temp_1 = tempa;
				temp_2 = tempb;
				break;
		}

		if (Telemetry_Get_PMBUS_Configuration((PMBUS_PAGE_t)loop, (TELEMETRY_CONFIG)TELEMETRY_CONFIG_FW_FILTER_EN) == 1) {
			/*lint -e702 */
			temp_1 = (temp_1 + (LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_READ_TEMPERATURE_1))))>>1u;
			/*lint -e702 */
			temp_2 = (temp_2 + (LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word((PMBUS_PAGE_t)loop, PMBUS_CMDCODE_READ_TEMPERATURE_2))))>>1u;
		}

		PMBUS_Set_Command_Word((PMBUS_PAGE_W_BROADCAST_t)loop, PMBUS_CMDCODE_READ_TEMPERATURE_1, ((uint16_t)temp_1 & 0x7ff));
		PMBUS_Set_Command_Word((PMBUS_PAGE_W_BROADCAST_t)loop, PMBUS_CMDCODE_READ_TEMPERATURE_2, ((uint16_t)temp_2 & 0x7ff));
	}

	uint16_t fan_speed1 = Telemetry_get_fan_speed(FAN1);
	uint16_t fan_speed2 = Telemetry_get_fan_speed(FAN2);

	// Get fan speed, replicate on both loops
	// since the bottom 8 lsb's of fan_speed register are always zero we shift those off and use +6 exponent to get 64 to 65k rpm
	int32_t temp = SHIFT_EXPONENT(fan_speed1, -(fan_read_exp[PMBUS_PAGE_0]));
	if (temp > 0x3ff) temp = 0x3ff;  // clamp fan speed at mantissa size
	PMBUS_Set_Command_Word(PMBUS_PAGE_WB_BROADCAST, (uint8_t)PMBUS_CMDCODE_READ_FAN_SPEED_1, (uint16_t)(((TWOS_COMPLEMENT (5, fan_read_exp[PMBUS_PAGE_0]))<<11)
			| temp));
	temp = SHIFT_EXPONENT(fan_speed2, -(fan_read_exp[PMBUS_PAGE_0]));  // shift the fan speed by the exponent
	if (temp > 0x3ff) temp = 0x3ff;  // clamp fan speed at mantissa size
	PMBUS_Set_Command_Word(PMBUS_PAGE_WB_BROADCAST, (uint8_t)PMBUS_CMDCODE_READ_FAN_SPEED_2, (uint16_t)(((TWOS_COMPLEMENT (5, fan_read_exp[PMBUS_PAGE_0]))<<11)
			| temp));

	call_system_cb(TELEMETRY_SAMPLE);

}


