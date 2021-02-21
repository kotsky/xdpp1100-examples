/*
 * uvp_warn.h
 *
 *  Created on: 4 DEC 2019
 *      Author: ashendar
 */

#ifndef SRC_USER_APP_VIN_UVP_H_
#define SRC_USER_APP_VIN_UVP_H_

#include "pmbus_autogen.h"      // PMBUS_PAGE_t
#include "telemetry_irq_handlers.h"

/**
 * Enable or disable various add on features here.
 */

#define vin_uvp

#ifdef vin_uvp
void Telemetry_IRQ_VIN_MFR_UVP_FAULT_HANDLE(Telemetry_IRQ_TYPE_t Telemetry_type);
#endif


#endif /* SRC_USER_APP_VIN_UVP_H_ */
