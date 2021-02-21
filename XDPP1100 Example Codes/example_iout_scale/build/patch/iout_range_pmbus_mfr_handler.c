/*
 * iout_scaling_pmbus_mfr_handler.c
 *
 *  Created on: 31 Oct 2019
 *      Author: halimand
 */


#include "iout_range_pmbus_mfr_handler.h"

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
 * @param page Selects the pmbus page to operate on.
 * @param direction Can either be PMBUS_WRITE or PMBUS_READ types
 */
void patch_PMBUS_HANDLE_IOUT_CAL_OFFSET(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	// if write:
	if ((direction == PMBUS_WRITE)||(direction == OTP_RESTORE))
	{
		int32_t value = LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_IOUT_CAL_OFFSET));
		int32_t exponent;
		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		exponent = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_IOUT_CAL_OFFSET)) - 1;
		/* iout scale Example Modification End */
		value = SHIFT_EXPONENT(value, (exponent-IOUT_CAL_OFFSET_EXPONENT));
		if (value > 0xff) value = 0xff;
		ISEN_ISP_APC__ISP_IOFFSET__SET((isen_idx_t)page, (uint32_t)value);
	}
}

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
 * @param page Selects the pmbus page to operate on.
 * @param direction Can either be PMBUS_WRITE or PMBUS_READ types
 */
void patch_PMBUS_HANDLE_IOUT_OC_FAULT_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	// if write:
	if (direction == PMBUS_WRITE)
	{
		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		int32_t exponent = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_IOUT_OC_FAULT_LIMIT)) - 1;
		/* iout scale Example Modification End */
		uint16_t mantissa = (uint16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_IOUT_OC_FAULT_LIMIT));
		uint8_t fault_response_cmd_byte = PMBUS_Get_Command_Byte(page, PMBUS_CMDCODE_IOUT_OC_FAULT_RESPONSE);
		FAULTS_SETUP_FAULT(page, FAULT_TYPE_IOUT_OC_FAULT, fault_response_cmd_byte,
								FAULTS_CONFIG_IOUT_DELAY_UNIT, CURRENT_RESPONSE_TYPE,
								(uint8_t)PMBUS_CMDCODE_STATUS_IOUT, (uint8_t)PMBUS_STATUS_IOUT_OC_FAULT, FAULT_TYPE_IOUT_OC_WARN);
		Fault_Threshold_Set(page, FAULT_TYPE_IOUT_OC_FAULT, (int32_t)mantissa, (int32_t)exponent);
	}
}

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
 * @param page Selects the pmbus page to operate on.
 * @param direction Can either be PMBUS_WRITE or PMBUS_READ types
 */
void patch_PMBUS_HANDLE_IOUT_UC_FAULT_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	// if write:
	if (direction == PMBUS_WRITE)
	{
		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		int32_t exponent = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_IOUT_UC_FAULT_LIMIT)) - 1;
		/* iout scale Example Modification End */
		int16_t mantissa = (int16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_IOUT_UC_FAULT_LIMIT));
		uint8_t fault_response_cmd_byte = PMBUS_Get_Command_Byte(page, PMBUS_CMDCODE_IOUT_UC_FAULT_RESPONSE);
		FAULTS_SETUP_FAULT(page, FAULT_TYPE_IOUT_UC_FAULT,fault_response_cmd_byte,
								FAULTS_CONFIG_IOUT_DELAY_UNIT, VOLTAGE_RESPONSE_TYPE,
								(uint8_t)PMBUS_CMDCODE_STATUS_IOUT, (uint8_t)PMBUS_STATUS_IOUT_UC_FAULT, (FAULT_TYPE_t) FAULT_TYPE_IOUT_UC_FAULT);
		Fault_Threshold_Set(page, FAULT_TYPE_IOUT_UC_FAULT, (int32_t)mantissa, (int32_t)exponent);
	}
}

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
 * @param page Selects the pmbus page to operate on.
 * @param direction Can either be PMBUS_WRITE or PMBUS_READ types
 */
void patch_PMBUS_HANDLE_IOUT_OC_WARN_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	// if write:
	if ((direction == PMBUS_WRITE)||(direction == OTP_RESTORE))
	{
		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		int32_t exponent = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_IOUT_OC_WARN_LIMIT)) - 1;
		/* iout scale Example Modification End */
		uint16_t mantissa = (uint16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_IOUT_OC_WARN_LIMIT));
		uint8_t fault_response_cmd_byte = (uint8_t)FAULT_RESPONSE_IGNORE;  // warn responses are basically ignore
		FAULTS_SETUP_FAULT(page, FAULT_TYPE_IOUT_OC_WARN, fault_response_cmd_byte,
								FAULTS_CONFIG_IOUT_DELAY_UNIT, VOLTAGE_RESPONSE_TYPE,
								(uint8_t)PMBUS_CMDCODE_STATUS_IOUT, (uint8_t)PMBUS_STATUS_IOUT_OC_WARNING, FAULT_TYPE_IOUT_OC_FAULT);
		Fault_Threshold_Set(page, FAULT_TYPE_IOUT_OC_WARN, (int32_t)mantissa, (int32_t)exponent);
	}
}

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
 * @param page Selects the pmbus page to operate on.
 * @param direction Can either be PMBUS_WRITE or PMBUS_READ types
 */
void patch_PMBUS_HANDLE_IIN_OC_FAULT_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	// if write:
	if (direction == PMBUS_WRITE)
	{
		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		int32_t exponent = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_IIN_OC_FAULT_LIMIT)) - 1;
		/* iout scale Example Modification End */
		uint16_t mantissa = (uint16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_IIN_OC_FAULT_LIMIT));
		uint8_t fault_response_cmd_byte = PMBUS_Get_Command_Byte(page, PMBUS_CMDCODE_IIN_OC_FAULT_RESPONSE);
		FAULTS_SETUP_FAULT(page, FAULT_TYPE_IIN_OC_FAULT, fault_response_cmd_byte,
								FAULTS_CONFIG_VIN_DELAY_UNIT, VOLTAGE_RESPONSE_TYPE,
								(uint8_t)PMBUS_CMDCODE_STATUS_INPUT, (uint8_t)PMBUS_STATUS_INPUT_IIN_OC_FAULT, FAULT_TYPE_IIN_OC_WARN);
		Fault_Threshold_Set(page, FAULT_TYPE_IIN_OC_FAULT, (int32_t)mantissa, (int32_t)exponent);

	}
}

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
 * @param page Selects the pmbus page to operate on.
 * @param direction Can either be PMBUS_WRITE or PMBUS_READ types
 */
void patch_PMBUS_HANDLE_IIN_OC_WARN_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	// if write:
	if ((direction == PMBUS_WRITE)||(direction == OTP_RESTORE))
	{
		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		int32_t exponent = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_IIN_OC_WARN_LIMIT)) - 1;
		/* iout scale Example Modification End */
		uint16_t mantissa = (uint16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_IIN_OC_WARN_LIMIT));
		uint8_t fault_response_cmd_byte = 0x00;//FAULT_RESPONSE_IGNORE;
		FAULTS_SETUP_FAULT(page, FAULT_TYPE_IIN_OC_WARN, fault_response_cmd_byte,
								FAULTS_CONFIG_VIN_DELAY_UNIT, VOLTAGE_RESPONSE_TYPE,
								(uint8_t)PMBUS_CMDCODE_STATUS_INPUT, (uint8_t)PMBUS_STATUS_INPUT_IIN_OC_WARNING, FAULT_TYPE_IIN_OC_FAULT);
		Fault_Threshold_Set(page, FAULT_TYPE_IIN_OC_WARN, (int32_t)mantissa, (int32_t)exponent);
	}
}

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
 * @param page Selects the pmbus page to operate on.
 * @param direction Can either be PMBUS_WRITE or PMBUS_READ types
 */
void patch_PMBUS_HANDLE_VOUT_DROOP(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	// if write:
	if ((direction == PMBUS_WRITE))
	{
		// Read vout_scale and vout_scale
		uint32_t vout_scale = PMBUS_Get_Vout_Scale(page, PMBUS_Q_EXP);
		uint32_t vout_droop = PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_VOUT_DROOP);
		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		int32_t vout_droop_exp = LINEAR11_TO_EXPONENT((uint16_t)vout_droop) + 1;
		/* iout scale Example Modification End */
		// Grab mantissa of vout droop
		vout_droop = (uint32_t)LINEAR11_TO_MANTISSA((uint16_t)vout_droop);

		// multiply droop by vout scale and shift to LOADLINE_EXP
		uint32_t mohms = (uint32_t)SHIFT_EXPONENT((int32_t)(vout_droop * vout_scale) , (-LOADLINE_EXP+vout_droop_exp+PMBUS_Q_EXP));
		if (mohms > 0x7ff) mohms = 0x7ff;  // cap at max
		VCONTROL_VC_VAVP3__VC_VAVP_RLL__SET((vcontrol_idx_t) page, mohms);
	}
}

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
 * @param page Selects the pmbus page to operate on.
 * @param direction Can either be PMBUS_WRITE or PMBUS_READ types
 */
void patch_PMBUS_HANDLE_FW_CONFIG_REGULATION(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	uint32_t vout_scale;
	uint32_t vout_droop;
	int32_t vout_droop_exp;

	// if write:
	if(direction == PMBUS_WRITE)
	{
		// Read vout_scale
		vout_scale = PMBUS_Get_Vout_Scale(page, PMBUS_Q_EXP);
		vout_droop = Regulation_Get_PMBUS_Configuration(page, REGULATION_CONFIG_MFR_RDROOP_RLL_SEG2);
		vout_droop_exp = LINEAR11_TO_EXPONENT((uint16_t)vout_droop);

		// Grab mantissa of vout droop
		vout_droop = (uint32_t)LINEAR11_TO_MANTISSA((uint16_t)vout_droop);

		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		// multiply droop by vout scale and shift to LOADLINE_EXP
		uint32_t mohms = (uint32_t)SHIFT_EXPONENT((int32_t)(vout_droop * vout_scale) , (1+vout_droop_exp+PMBUS_Q_EXP + 1));
		/* iout scale Example Modification End */

		if (mohms > 0x3ff) mohms = 0x3ff;  // cap at max
		VCONTROL_VC_VAVP5__VC_VAVP_RLL_SEG2__SET((vcontrol_idx_t) page, mohms);

		vout_droop = Regulation_Get_PMBUS_Configuration(page, REGULATION_CONFIG_MFR_RDROOP_RLL_SEG3);
		vout_droop_exp = LINEAR11_TO_EXPONENT((uint16_t)vout_droop);

		// Grab mantissa of vout droop
		vout_droop = (uint32_t)LINEAR11_TO_MANTISSA((uint16_t)vout_droop);

		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		// multiply droop by vout scale and shift to LOADLINE_EXP
		mohms = (uint32_t)SHIFT_EXPONENT((int32_t)(vout_droop * vout_scale) , (1+vout_droop_exp+PMBUS_Q_EXP + 1));
		/* iout scale Example Modification End */

		if (mohms > 0x3ff) mohms = 0x3ff;  // cap at max
		VCONTROL_VC_VAVP6__VC_VAVP_RLL_SEG3__SET((vcontrol_idx_t) page, mohms);

		vout_droop = Regulation_Get_PMBUS_Configuration(page, REGULATION_CONFIG_MFR_RDROOP_RLL_NEG);
		vout_droop_exp = LINEAR11_TO_EXPONENT((uint16_t)vout_droop);

		// Grab mantissa of vout droop
		vout_droop = (uint32_t)LINEAR11_TO_MANTISSA((uint16_t)vout_droop);

		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		// multiply droop by vout scale and shift to LOADLINE_EXP
		mohms = (uint32_t)SHIFT_EXPONENT((int32_t)(vout_droop * vout_scale) , (7+vout_droop_exp+PMBUS_Q_EXP) + 1);
		/* iout scale Example Modification End */

		if (mohms > 0x7ff) mohms = 0x7ff;  // cap at max
		VCONTROL_VC_VAVP4__VC_VAVP_RLL_NEG__SET((vcontrol_idx_t) page, mohms);

		vout_droop = Regulation_Get_PMBUS_Configuration(page, REGULATION_CONFIG_MFR_RDROOP_ITHR_SEG2);

		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		// Write threshold register for seg2
		mohms = (uint32_t)SHIFT_EXPONENT(LINEAR11_TO_MANTISSA((uint16_t)vout_droop), (1 + LINEAR11_TO_EXPONENT((uint16_t)vout_droop) - 1));
		/* iout scale Example Modification End */
		VCONTROL_VC_VAVP7__VC_VAVP_ITHR_SEG2__SET((vcontrol_idx_t) page, mohms);

		vout_droop = Regulation_Get_PMBUS_Configuration(page, REGULATION_CONFIG_MFR_RDROOP_ITHR_SEG3);

		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		// Write threshold register for seg3
		mohms = (uint32_t)SHIFT_EXPONENT(LINEAR11_TO_MANTISSA((uint16_t)vout_droop), (1 + LINEAR11_TO_EXPONENT((uint16_t)vout_droop) - 1));
		/* iout scale Example Modification End */
		VCONTROL_VC_VAVP8__VC_VAVP_ITHR_SEG3__SET((vcontrol_idx_t) page, mohms);
	}
}

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
 * @param page Selects the pmbus page to operate on.
 * @param direction Can either be PMBUS_WRITE or PMBUS_READ types
 */
void patch_PMBUS_HANDLE_MFR_IOUT_OC_FAST_FAULT_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	// if write:
	if (direction == PMBUS_WRITE)
	{
		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		int32_t exponent = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_MFR_IOUT_OC_FAST_FAULT_LIMIT)) - 1;
		/* iout scale Example Modification End */
		int16_t mantissa = (int16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_MFR_IOUT_OC_FAST_FAULT_LIMIT));
		uint8_t fault_response_cmd_byte = PMBUS_Get_Command_Byte(page, PMBUS_CMDCODE_MFR_IOUT_OC_FAST_FAULT_RESPONSE);
		FAULTS_SETUP_FAULT(page, FAULT_TYPE_MFR_IOUT_OC_FAST, fault_response_cmd_byte,
								FAULTS_CONFIG_IOUT_DELAY_UNIT, CURRENT_RESPONSE_TYPE,
								(uint8_t)PMBUS_CMDCODE_STATUS_MFR_SPECIFIC, (uint8_t)PMBUS_STATUS_MFR_SPECIFIC_5, (FAULT_TYPE_t) FAULT_TYPE_MFR_IOUT_OC_FAST);

		Fault_Threshold_Set(page, FAULT_TYPE_MFR_IOUT_OC_FAST, (int32_t)mantissa, (int32_t)exponent);
	}
}

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
 * @param page Selects the pmbus page to operate on.
 * @param direction Can either be PMBUS_WRITE or PMBUS_READ types
 */
void patch_PMBUS_HANDLE_MFR_IOUT_APC(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	// if write:
	if ((direction == PMBUS_WRITE)||(direction == OTP_RESTORE))
	{
		uint32_t value = (uint32_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_MFR_IOUT_APC));
		int32_t exponent;
		/* iout scale Example Modification Start */
		//changes from the original PMBUS handler
		exponent = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_MFR_IOUT_APC)) - 1;
		/* iout scale Example Modification End */
		value = (uint32_t)SHIFT_EXPONENT((int32_t)value, (exponent-ISEN_APC_EXPONENT));
		if (value > 0x7ff) value = 0x7ff;  // cap at field max
		ISEN_ISP_APC__ISP_APC__SET((isen_idx_t)page, value);
	}
}

