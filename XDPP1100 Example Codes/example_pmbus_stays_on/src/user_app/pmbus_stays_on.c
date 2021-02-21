/*
 * patch_pmbus_stays_on.c
 *
 *  Created on: 27 Feb 2020
 *      Author: halimand
 */

#include "pmbus_stays_on.h"

/**
 * Function modification for PMBus stays ON replace ROM function
 * @param loop Selects the pmbus page to operate on.
 * @param state Selects the state at which power mode is applied
 */
void patch_Regulation_Shutdown_Sequence (PMBUS_PAGE_t loop, REGULATION_STATE state, REGULATION_CONTROLS control)
{

	//////////////SHUTDOWN SEQUENCE//////////////
	//Mask faults
	Regulation_Fault_Mask (loop, state, control);

	Regulation_PWM_Control(loop, REGULATION_PWMS_OFF);  // ALL FET's OFF
	Regulation_Set_VID(loop, 0, 0, 0, 0, 1);
	VCONTROL_VC_VRAMP1__VC_VRAMP_ON__SET((vcontrol_idx_t)loop, 0);  // turn off vramp_on signal to allow pwms to stop regulation
	// clear the interrupt here in case it was left over from a fault
	VCONTROL_VC_IRQ__VC_VCONTROL_IRQ_EN__SET((vcontrol_idx_t) loop, 0);

	//disable the hardware blocks: (telemetry and faults are always active but masked at different times)
	Regulation_Power_Mode (loop, state);

	if (loop == PMBUS_PAGE_0)
	{
		// disable ton_max interrupts
		TLMCOM_TLM_IRQ_EN__TLM_IRQ_EN__SET(TLMCOM_TLM_IRQ_EN__TLM_IRQ_EN__GET() &
																	~((1u<<(uint32_t)VOUT_UV_TON_MAX_DISABLE_0)));
	}
	else
	{
		// disable ton_max interrupts
		TLMCOM_TLM_IRQ_EN__TLM_IRQ_EN__SET(TLMCOM_TLM_IRQ_EN__TLM_IRQ_EN__GET() &
																		~((1u<<(uint32_t)VOUT_UV_TON_MAX_DISABLE_1)));
	}

	// update status word from result:
	PMBUS_Inter_Thread_Set_Command((PMBUS_PAGE_W_BROADCAST_t)loop, PMBUS_CMDCODE_STATUS_WORD, PMBUS_READ);

	// Clear HW Fault Shutdown mask
	FAULT_FAULT_SHUT_CLR_LOOP__FAULT_SHUT_CLR_LOOP__SET((fault_idx_t) REGULATION_APP.loop, 1) ;

	if (loop == PMBUS_PAGE_0)
	{
	FAULTCOM_FAULT_SHUT_CLR_COM__FAULT_SHUT_CLR_COM__SET(1) ;
	}

	call_system_cb(SHUTDOWN_SEQUENCE);

}

/**
 * Function modification for PMBus stays ON replace ROM function
 * mode = 0 low power mode
 * mode = 1 high power active mode
 * topo : ACF=0, spare=1, HBCT=2, HBFW=3, spare=4, FBCT=5, FBFW=6, spare=7
 * @param loop Selects the pmbus page to operate on.
 * @param state Selects the state at which power mode is applied
 */
void patch_Regulation_Power_Mode (PMBUS_PAGE_t loop, REGULATION_STATE state)
{

	uint32_t reg1 = COMMON_EN_REG1__GET();
	uint32_t reg2 = COMMON_EN_REG2__GET();
	uint32_t common = COMMON_EN_REG3__GET();
	uint8_t topo = (uint8_t)Regulation_Get_PMBUS_Configuration(loop, REGULATION_CONFIG_TOPOLOGY);
	boolean interleave_enable = (uint8_t)Regulation_Get_PMBUS_Configuration(loop, REGULATION_CONFIG_INTERLEAVE_ENABLE);
	boolean second_current_sense = (Regulation_Get_PMBUS_Configuration(loop, REGULATION_CONFIG_CURRENT_DOUBLER_ENABLE))
			|| (Regulation_Get_PMBUS_Configuration(loop, REGULATION_CONFIG_EN_PRIM_ISENSE));
	uint32_t power_mode = PMBUS_Get_Command_Byte(loop, PMBUS_CMDCODE_POWER_MODE);
	TELEMETRY_VIN_SOURCE source = Telemetry_get_vin_source(loop);
	boolean vrect_sense = 0;
	if ( (source == (TELEMETRY_VIN_SOURCE)TELEMETRY_VIN_SOURCE_VRECT1) || (source == (TELEMETRY_VIN_SOURCE)TELEMETRY_VIN_SOURCE_VRECT2) )
	{
		vrect_sense = 1;
	}
	switch (state)
	{
		case (REGULATION_STATE_OFF) :

			// in state off we zero out anything that is not set in regulation_state_off (or in the others at init)
			// first we or in the static enables for common these are always enabled in all topologies for either loop:
			common |= (COMMON_EN_REG3__EN_TSP__Msk | COMMON_EN_REG3__EN_TSEN__Msk
						| COMMON_EN_REG3__EN_TS__Msk | COMMON_EN_REG3__EN_TELEMC__Msk
						| COMMON_EN_REG3__EN_FAULTC__Msk);

			common &= ~(COMMON_EN_REG3__EN_IBAL__Msk
						| COMMON_EN_REG3__EN_FBAL__Msk
						| COMMON_EN_REG3__EN_FBAL2__Msk
						| COMMON_EN_REG3__EN_ISHARE__Msk);  // clear ibal and fbal enables in all topos (re-enable in later state)


			// now zero out loop specific bits not enabled in off state (things that have integrators that need reset:
			if(loop == PMBUS_PAGE_0)
			{
				reg1 &= (COMMON_EN_REG1__EN_RAMP0__Msk);  // zero others

				/*  PMBus stays ON Example modification Start*/
				reg1 |= ( COMMON_EN_REG1__EN_RAMP0__Msk
						| COMMON_EN_REG1__EN_FAULT0__Msk
						| COMMON_EN_REG1__EN_VCONTROL0__Msk
						| COMMON_EN_REG1__EN_TELEM0__Msk
						| COMMON_EN_REG1__EN_CE0__Msk
						| COMMON_EN_REG1__EN_VSP0__Msk
						| COMMON_EN_REG1__EN_VS0__Msk
						| COMMON_EN_REG1__EN_VSP1__Msk // handled below
						| COMMON_EN_REG1__EN_VS1__Msk // handled below
						| COMMON_EN_REG1__EN_IS0__Msk
						| COMMON_EN_REG1__EN_ISP1__Msk);
				/*  PMBus stays ON Example modification End*/
			}
			else  // loop 1
			{
				reg2 &= (COMMON_EN_REG2__EN_RAMP1__Msk);  // zero others

				/*  PMBus stays ON Example modification Start*/
				reg2 |= (COMMON_EN_REG2__EN_RAMP1__Msk
						| COMMON_EN_REG2__EN_FAULT1__Msk
						| COMMON_EN_REG2__EN_VCONTROL1__Msk
						| COMMON_EN_REG2__EN_TELEM1__Msk
						| COMMON_EN_REG2__EN_CE1__Msk // handled below
						| COMMON_EN_REG2__EN_VSP2__Msk // handled below
						| COMMON_EN_REG2__EN_VS2__Msk // handled below
						| COMMON_EN_REG2__EN_IS1__Msk // handled below
						| COMMON_EN_REG2__EN_ISP2__Msk // handled below
						);  // set these per loop
				/*  PMBus stays ON Example modification End*/

			}

			// shasta-578 if we are using vrect sense as the prisen
			// for faster feed forward then enable vs/vsp in off state:
			if(source == (TELEMETRY_VIN_SOURCE)TELEMETRY_VIN_SOURCE_VRECT1_VIN_PRISEN)
			{
				reg1 |= COMMON_EN_REG1__EN_VSP1__Msk | COMMON_EN_REG1__EN_VS1__Msk;
			}
			else if(source == (TELEMETRY_VIN_SOURCE)TELEMETRY_VIN_SOURCE_VRECT2_VIN_PRISEN)
			{
				reg2 |= COMMON_EN_REG2__EN_VSP2__Msk | COMMON_EN_REG2__EN_VS2__Msk;
			}

			/*  PMBus stays ON Example modification Start - remove these lines because it will disable BISEN */
			// zero out the current estimator block when using primary current sense
//			if (second_current_sense!=0)
//			{
//				reg2 &= ~(COMMON_EN_REG2__EN_CE1__Msk | COMMON_EN_REG2__EN_IS1__Msk | COMMON_EN_REG2__EN_ISP2__Msk);
//			}
			/*  PMBus stays ON Example modification End*/

			break;

		case (REGULATION_STATE_TON_DELAY) :

			// LOOP SPECIFIC ENABLES:
			if(loop == PMBUS_PAGE_0)
			{
				reg1 |= COMMON_EN_REG1__EN_VSP0__Msk | COMMON_EN_REG1__EN_VS0__Msk | COMMON_EN_REG1__EN_CE0__Msk
					| COMMON_EN_REG1__EN_IS0__Msk | COMMON_EN_REG1__EN_ISP1__Msk
					| COMMON_EN_REG1__EN_VSP1__Msk | COMMON_EN_REG1__EN_TELEM0__Msk | COMMON_EN_REG1__EN_VS1__Msk;
			}
			else
			{
				reg2 |= COMMON_EN_REG2__EN_CE1__Msk | COMMON_EN_REG2__EN_IS1__Msk | COMMON_EN_REG2__EN_ISP2__Msk
						| COMMON_EN_REG2__EN_TELEM1__Msk
						| COMMON_EN_REG2__EN_VSP2__Msk | COMMON_EN_REG2__EN_VS2__Msk;
			}

			// TOPOLOGY SPECIFIC ENABLES:
			if (interleave_enable!=0)  // disable loop 1 things when here
			{
				reg2 &= ~(COMMON_EN_REG2__EN_VCONTROL1__Msk | COMMON_EN_REG2__EN_PID1__Msk
					| COMMON_EN_REG2__EN_TELEM1__Msk | COMMON_EN_REG2__EN_FAULT1__Msk);
				reg2 |= COMMON_EN_REG2__EN_CE1__Msk | COMMON_EN_REG2__EN_IS1__Msk | COMMON_EN_REG2__EN_ISP2__Msk
					| COMMON_EN_REG2__EN_FAULT1__Msk | COMMON_EN_REG2__EN_VSP2__Msk | COMMON_EN_REG2__EN_VS2__Msk;
			}

			// enable the current estimator block when using primary current sense
			if (second_current_sense!=0)
			{
				reg2 |= (COMMON_EN_REG2__EN_CE1__Msk | COMMON_EN_REG2__EN_IS1__Msk | COMMON_EN_REG2__EN_ISP2__Msk);
			}

			break;

		case (REGULATION_STATE_TON_RISE) :
			// LOOP SPECIFIC ENABLES:
			if(loop == PMBUS_PAGE_0)
			{
				reg1 |= COMMON_EN_REG1__EN_PWM0__Msk | COMMON_EN_REG1__EN_PID0__Msk
					| COMMON_EN_REG1__EN_VCONTROL0__Msk | COMMON_EN_REG1__EN_PID_OSP0__Msk;
			}
			else
			{
				reg2 |= COMMON_EN_REG2__EN_PWM1__Msk | COMMON_EN_REG2__EN_PID1__Msk
										| COMMON_EN_REG2__EN_VCONTROL1__Msk  | COMMON_EN_REG2__EN_PID_OSP1__Msk;
			}

			// TOPOLOGY SPECIFIC ENABLES:
			if (interleave_enable!=0)
			{
				common |= COMMON_EN_REG3__EN_IBAL__Msk;
			}
			if ((topo==(uint8_t)REGULATION_TOPOLOGY_FB_CT)
								|| (topo==(uint8_t)REGULATION_TOPOLOGY_FB_FW)
								|| (topo==(uint8_t)REGULATION_TOPOLOGY_HB_FW)
								|| (topo==(uint8_t)REGULATION_TOPOLOGY_HB_CT)
							)
			{
				uint32_t mode_control = PWM_RAMP_CONFIG__MODE_CONTROL_LOOP0__GET();
				if (mode_control==0)
				{
					common |= COMMON_EN_REG3__EN_FBAL__Msk;
				}
				if ((interleave_enable!=0)&&(mode_control==0))
				{
					common |= COMMON_EN_REG3__EN_FBAL2__Msk;
				}
			}

			break;

		case (REGULATION_STATE_AT_TARGET_VID) :

			// disable the pid osp when not in the ton_rise state:
			if(loop == PMBUS_PAGE_0)
			{
				reg1 &= ~COMMON_EN_REG1__EN_PID_OSP0__Msk;
			}
			else
			{
				reg2 &= ~COMMON_EN_REG2__EN_PID_OSP1__Msk;
			}

			if ((power_mode==0) && (topo!=(uint8_t)REGULATION_TOPOLOGY_ACF) && (!interleave_enable)) {
				if(loop == PMBUS_PAGE_0)
				{
					reg1 |= (COMMON_EN_REG1__EN_BURST0__Msk);
				}
				else  // loop 1
				{
					reg2 |= (COMMON_EN_REG2__EN_BURST1__Msk);
				}
			}
			break;

		case (REGULATION_STATE_FAULT) :

			//Turn off vin in vrect sense.
			//This will force the value to zero.
			if (vrect_sense)
			{
				if(loop == PMBUS_PAGE_0)
				{
					reg1 &= ~(COMMON_EN_REG1__EN_VSP1__Msk);
				}
				else  // loop 1
				{
					reg2 &= ~(COMMON_EN_REG2__EN_VSP2__Msk);
				}
			}
			break;

		default:
			break;
	}
	COMMON_EN_REG3__SET(common);
	COMMON_EN_REG1__SET(reg1);
	COMMON_EN_REG2__SET(reg2);
}



