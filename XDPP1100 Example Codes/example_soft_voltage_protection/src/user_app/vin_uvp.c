/*
 * uvp_warn.c
 *
 *  Created on: 4 DEC 2019
 *      Author: ashendar
 */

#include "vin_uvp.h"

#ifdef vin_uvp

#include "pmbus_mfr_autogen.h"
#include "pmbus_autogen.h"      // PMBUS_PAGE_t
#include "pmbus_api.h"
#include "telemetry_api.h"
#include "faults_api.h"
#include "telemetry_irq_handlers.h"
#include "faults_drv.h"
#define FAULT_TYPE_VIN_UVP fw_spare3  //using firmware spare bit for FAULT_TYPE
#define TELEM_IRQ_VIN_UVP TELEM_IRQ9  //using IRQ9 of generic interrupts (total 16 supported)

uint32_t pmbus_mfr_uvp_warn_delay;

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
 * Setup fault threshold to trigger soft-VIN UVP
 * @param page Selects the pmbus page to operate on.
 * @param direction Can either be PMBUS_WRITE or PMBUS_READ types
 */
void PMBUS_HANDLE_MFR_VIN_UV_FAULT_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	if ((direction == PMBUS_WRITE) && (page == PMBUS_PAGE_0)) //loop0 only
	{
		//assumes fault limit is in VOUT_MODE format
		//Since polarity is inverse. hysteresis is the actual threshold
		int32_t hysteresis_exponent = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_MFR_VIN_UV_FAULT_LIMIT));
		uint16_t hysteresis_mantissa = (uint16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_MFR_VIN_UV_FAULT_LIMIT));

		int32_t exponent = LINEAR11_TO_EXPONENT(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_VIN_UV_WARN_LIMIT));
		uint16_t mantissa = (uint16_t)LINEAR11_TO_MANTISSA(PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_VIN_UV_WARN_LIMIT));

		Telemetry_Set_Irq_Threshold(TELEM_IRQ_VIN_UVP, (int32_t)mantissa, (int8_t)exponent);
		Telemetry_Set_Irq_Hysteresis_Threshold(TELEM_IRQ_VIN_UVP, (int32_t)hysteresis_mantissa, (int8_t)hysteresis_exponent);

		//Setup for telemetry IRQ callback/handle
		uint16_t telem;
		telem = (uint16_t)TLMCOM_TLM_IRQ_EN__TLM_IRQ_EN__GET();
		//Clear hardware interrupt
		TLMCOM_TLM_IRQ_EN__TLM_IRQ_EN__SET(telem &~(1u<<(uint32_t)TELEM_IRQ_VIN_UVP));

		_Telemetry_s * Telemetry_str = Telemetry_GET_ARRAY_POINTER(TELEM_IRQ_VIN_UVP) ;
		Telemetry_str->loop = page;
		Telemetry_str->source = VIN_0;
		//Set the handle
		Telemetry_IRQ_Event_Handle_Set(TELEM_IRQ_VIN_UVP, Telemetry_IRQ_VIN_MFR_UVP_FAULT_HANDLE);
		//Set initial polarity to below the hysteresis threshold
		Telemetry_Set_Irq_Polarity(TELEM_IRQ_VIN_UVP, 1);

		uint8_t fault_response_cmd_byte = PMBUS_Get_Command_Byte(page, PMBUS_CMDCODE_MFR_VIN_UV_FAULT_RESPONSE);

		//SETUP response and reporting on STATUS MFR SPECIFIC bit 1
		FAULTS_SETUP_FAULT(page, FAULT_TYPE_VIN_UVP, fault_response_cmd_byte,
					FAULTS_CONFIG_VIN_DELAY_UNIT, VOLTAGE_RESPONSE_TYPE,
						(uint8_t)PMBUS_CMDCODE_STATUS_MFR_SPECIFIC, (uint8_t)PMBUS_STATUS_MFR_SPECIFIC_2, FAULT_TYPE_VIN_UVP);

		// enable telemetry interrupt
		Telemetry_Enable_IRQ_Type(TELEM_IRQ_VIN_UVP);
	}
}

/**
 * This function is Telem event callback for soft-VIN_UVP.
 * @param Telemetry_type
 */
void Telemetry_IRQ_VIN_MFR_UVP_FAULT_HANDLE(Telemetry_IRQ_TYPE_t Telemetry_type)
{
	_Telemetry_s * Telemetry_str = Telemetry_GET_ARRAY_POINTER(Telemetry_type);
	if(Telemetry_str->polarity == 0) // reverse the polarity
	{
		//VIN below hysteresis level
		_FAULT_DESC_s * fault;
		//overwrite the delay to shutdown
		fault = FAULTS_GET_ARRAY_POINTER(PMBUS_PAGE_0, FAULT_TYPE_VIN_UVP);
		if (fault == NULL)
		{
			PMBUS_Log_Error(FAULTS, PROGRAM_COUNTER, PMBUS_STATUS_CML_PROCESSOR_FAULT);
			return;
		}

		pmbus_mfr_uvp_warn_delay = fault->delay_time_ms; //save the value of delay from pmbus command

		fault->delay_time_ms = 10; //set the delay to shutdown

		Set_Firmware_Fault(PMBUS_PAGE_0, FAULT_TYPE_VIN_UVP);
	}
	else
	{
		//VIN above the limit
		// set the delay to retry
		_FAULT_DESC_s * fault;
		fault = FAULTS_GET_ARRAY_POINTER(PMBUS_PAGE_0, FAULT_TYPE_VIN_UVP);
		if (fault == NULL)
		{
			PMBUS_Log_Error(FAULTS, PROGRAM_COUNTER, PMBUS_STATUS_CML_PROCESSOR_FAULT);
			return;
		}

		//set the delay to retry
		fault->delay_time_ms = pmbus_mfr_uvp_warn_delay; //

		Clear_Firmware_Fault(PMBUS_PAGE_0, FAULT_TYPE_VIN_UVP);
	}
}

#endif
