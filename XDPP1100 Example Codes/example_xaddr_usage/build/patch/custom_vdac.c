/*
 * custom_vdac.c
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
** Created on:  2020-11-20
*/

/* XADDR Usage: Custom VDAC Example Modification */

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

#include "custom_vdac.h"
#include "custom_vout_command_lut.h"
#include "regulation_state_machine_callbacks.h"


/*
 * Set your initial settings in vdac_config()
 * like desired idac, LUT settings, etc.
 */

void vdac_config()
{
	user_data.idac = 32;	// set your idac value, LSB = 0.625 uA
	user_data.vout_command_exp = -8;
}


/*
 * xaddr_resistance_measurement() shows a process flow
 * 1) to set XADDR1 pin configuration;
 * 2) to measure voltage at XADDR1 (vdac);
 * 3) to calculate measured resistance at
 * XADDR1 pin (res_meas);
 * 4) to set respective output voltage target
 * based on res_meas.
 * @param loop - index of current control loop
 * @return None
 */

void xaddr_resistance_measurement(PMBUS_PAGE_t loop)
{
	vdac_config();

	// Default vdac initialization: enable idac current source
	uint8_t xaddr1_pd = COMMON_XADDR1__XADDR1_PD__GET();
	uint32_t muxctrl2 = TSEN_TSEN_EN__TS_MUXCTRL2__GET();
	uint32_t ts_muxmode = TSEN_TSEN_EN__TS_MUXMODE__GET();

	TSEN_TSEN_EN__TS_MUXCTRL2__SET(5);
	TSEN_TSEN_EN__TS_MUXMODE__SET(0);
	TSEN_TSEN_EN__TS_TSIDAC_XV1_SEL__SET(1);	// to enable XADDR1 current source
	TSEN_TSEN_EN__XV_PINSET1_MEAS__SET(1);		// to enable XADDR1 pinset measure control
	TSEN_TSEN_EN__XV_DECODE_SEL__SET(1);
	COMMON_IDAC_FW__IDAC_FW_EN__SET(1);			// to enable FW forced idac current source
	COMMON_XADDR1__XADDR1_PD__SET(0);
	COMMON_IDAC_FW__IDAC_FW_FRC__SET(user_data.idac);		// iadc current
	// End default initialization

	// wait 10 ms to settle TADC.
	// this time can be reduced
	for(uint32_t i=0; i<100; i++)
	{
		 sys_delay_by_us(100);
	}

	uint16_t vdac_xaddr = vdac_xaddr_measurement(loop);	// vdac measurement

	vout_command_set(loop, vdac_xaddr);	// set vout_command based on measured vdac

	// Default settings
	// Disable iadc current source
	COMMON_IDAC_FW__IDAC_FW_FRC__SET(0);
	COMMON_IDAC_FW__IDAC_FW_EN__SET(0);
	COMMON_XADDR1__XADDR1_PD__SET(xaddr1_pd);
	TSEN_TSEN_EN__XV_PINSET1_MEAS__SET(0);
	TSEN_TSEN_EN__TS_TSIDAC_XV1_SEL__SET(0);
	TSEN_TSEN_EN__XV_DECODE_SEL__SET(0);
	TSEN_TSEN_EN__TS_MUXCTRL2__SET(muxctrl2);
	TSEN_TSEN_EN__TS_MUXMODE__SET(ts_muxmode);  // return to otp value

	// The system is ready to come into TON_RISE state.	 */
}


/*
 * vdac_xaddr_calculation() measures a voltage level
 * at XADDR1 pin, where max measured voltage can be
 * up to 1.2 V, and LSB is 0.1465.
 * @param loop - index of current control loop
 * @return vdac_xaddr - voltage level from XADDR
 */

uint16_t vdac_xaddr_measurement(PMBUS_PAGE_t loop)
{
	uint16_t vdac_xaddr;
	// tlm_xaddr1_adc_lpf
	vdac_xaddr = TLMCOM_TLM_XADDR1_LPF__TLM_XADDR1_ADC_LPF__GET();	// LSB = 0.1465 mV

	// averaging with 8 samples
	// which takes 700us max total
	for(uint8_t i=0; i<7; i++)
	{
		 sys_delay_by_us(100);
		 vdac_xaddr += TLMCOM_TLM_XADDR1_LPF__TLM_XADDR1_ADC_LPF__GET();
	}
	vdac_xaddr >>= 3;
	return vdac_xaddr;
}


/*
 * vout_command_set() sets output voltage target
 * based on measured vdac at XADDR1 pin.
 * This function can be changed by user to
 * set his own desired parameters in XDPP1100
 * @param loop - index of current control loop
 * @param vdac_xaddr - voltage level from XADDR
 * @return None
 */

void vout_command_set(PMBUS_PAGE_t loop, uint16_t vdac_xaddr)
{
	// Measured resistance res_xaddr = vdac / idac
	// LSB res = LSB vdac / LSB idac = 0.1465 mV / 0.625 uA = 0.2344 kOhm
	uint16_t res_xaddr;

	res_xaddr = ((vdac_xaddr << 16) / user_data.idac) >> 15;  // LSB = 0.2344 kOhm / 2 => LSB = 0.1172 kOhm

	// set calculated resistance with 0.1172 kOhm LSB to 0xB1 MFR PMBus Command MFR_VOUT_RES_MEAS
	PMBUS_Set_Command_Word(loop, PMBUS_CMDCODE_MFR_VOUT_RES_MEAS, res_xaddr);

	user_data.vout_command = vout_command_lut[1][0];	// set "0" as default

	// Matching measured resistance with Vout Command LUT
	for (uint8_t i = 0; i < VOUT_COMMAND_ROWS; i++)
	{
		if (res_xaddr <= vout_command_lut[0][i])
		{
			 user_data.vout_command = vout_command_lut[1][i];
			 user_data.vout_mode = PMBUS_Get_Vout_Mode_Exponent(loop);

			 // convert vout_command value from its LUT to vout_mode
			 user_data.vout_command = SHIFT_EXPONENT_UNSIGNED(user_data.vout_command,
																user_data.vout_command_exp - user_data.vout_mode);
			 break;
		}
	}

	// set respective vout_command according to measured resistance res_tsadc_xaddr
	PMBUS_Set_Command_Word(loop, PMBUS_CMDCODE_VOUT_COMMAND, user_data.vout_command);
}
