
#include "ovp_fault.h"

#ifdef ovp_fault

#include "pmbus_mfr_autogen.h"
#include "pmbus_autogen.h"      // PMBUS_PAGE_t
#include "pmbus_api.h"
#include "telemetry_api.h"
#include "faults_api.h"
#include "telemetry_irq_handlers.h"
#include "faults_drv.h"
#define FAULT_TYPE_OVP_FAULT fw_spare2  //using firmware spare bit for FAULT_TYPE
#define TELEM_IRQ_OVP_FAULT TELEM_IRQ6  //using IRQ6 of generic interrupts (total 16 supported)

uint32_t pmbus_mfr_ovp_fault_delay;

/**
 * Callback or Handle function called by pmbus thread after a read or write of given command
 * Setup fault threshold to trigger soft-OVP
 * @param page Selects the pmbus page to operate on.
 * @param direction Can either be PMBUS_WRITE or PMBUS_READ types
 */
void PMBUS_HANDLE_MFR_OVP_FAULT_LIMIT(PMBUS_PAGE_t page, PMBUS_DIRECTION_e direction)
{
	// if write
	if ((direction == PMBUS_WRITE) && (page == PMBUS_PAGE_0)) //loop0 only
	{
		//assumes fault limit is in VOUT_MODE format
		uint16_t mantissa = PMBUS_Get_Command_Word(page, PMBUS_CMDCODE_MFR_OVP_FAULT_LIMIT);
		int32_t  exponent = PMBUS_Get_Vout_Mode_Exponent(page);

		//for ex., set hysteresis to around 10% of threshold
		uint16_t hysteresis_mantissa = mantissa - (mantissa >> 3);
		int32_t  hysteresis_exponent = exponent;


		Telemetry_Set_Irq_Threshold(TELEM_IRQ_OVP_FAULT, (int32_t)mantissa, (int8_t)exponent);
		Telemetry_Set_Irq_Hysteresis_Threshold(TELEM_IRQ_OVP_FAULT, (int32_t)hysteresis_mantissa, (int8_t)hysteresis_exponent);
		Telemetry_Setup_Irq(page, VOUT_0, TELEM_IRQ_OVP_FAULT, Telemetry_IRQ_VOUT_MFR_OVP_FAULT_HANDLE);

		uint8_t fault_response_cmd_byte = PMBUS_Get_Command_Byte(page, PMBUS_CMDCODE_MFR_OVP_FAULT_RESPONSE);

		//SETUP response and reporting on STATUS MFR SPECIFIC bit 1
		FAULTS_SETUP_FAULT(page, FAULT_TYPE_OVP_FAULT, fault_response_cmd_byte,
						FAULTS_CONFIG_VOUT_DELAY_UNIT, VOLTAGE_RESPONSE_TYPE,
						(uint8_t)PMBUS_CMDCODE_STATUS_MFR_SPECIFIC, (uint8_t)PMBUS_STATUS_MFR_SPECIFIC_1, FAULT_TYPE_OVP_FAULT);

		// enable telemetry interrupt
		Telemetry_Enable_IRQ_Type(TELEM_IRQ_OVP_FAULT);
	}
}



/**
 * This function is Telem event callback for soft-OVP.
 * @param Telemetry_type
 */
void Telemetry_IRQ_VOUT_MFR_OVP_FAULT_HANDLE(Telemetry_IRQ_TYPE_t Telemetry_type)
{
	_Telemetry_s * Telemetry_str = Telemetry_GET_ARRAY_POINTER(Telemetry_type);
	if(Telemetry_str->polarity == 1)
	{
		//VOUT above the limit
		_FAULT_DESC_s * fault;
		//overwrite the delay to shutdown
		fault = FAULTS_GET_ARRAY_POINTER(PMBUS_PAGE_0, FAULT_TYPE_OVP_FAULT);
		if (fault == NULL)
		{
			PMBUS_Log_Error(FAULTS, PROGRAM_COUNTER, PMBUS_STATUS_CML_PROCESSOR_FAULT);
			return;
		}

		pmbus_mfr_ovp_fault_delay = fault->delay_time_ms; //save the value of delay from pmbus command

		fault->delay_time_ms = 10; //set the delay to shutdown

		Set_Firmware_Fault(PMBUS_PAGE_0, FAULT_TYPE_OVP_FAULT);
	}
	else
	{
		//VOUT below hysteresis level

		// set the delay to retry
		_FAULT_DESC_s * fault;
		fault = FAULTS_GET_ARRAY_POINTER(PMBUS_PAGE_0, FAULT_TYPE_OVP_FAULT);
		if (fault == NULL)
		{
			PMBUS_Log_Error(FAULTS, PROGRAM_COUNTER, PMBUS_STATUS_CML_PROCESSOR_FAULT);
			return;
		}

		//set the delay to retry
		fault->delay_time_ms = pmbus_mfr_ovp_fault_delay; //

		Clear_Firmware_Fault(PMBUS_PAGE_0, FAULT_TYPE_OVP_FAULT);
	}
}

#endif
