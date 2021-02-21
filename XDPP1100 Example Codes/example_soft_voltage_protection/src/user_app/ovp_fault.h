
#ifndef OVP_FAULT_H_
#define OVP_FAULT_H_

#include "pmbus_autogen.h"      // PMBUS_PAGE_t
#include "telemetry_irq_handlers.h"

//ADD-ON Features:

/**
 * Enable or disable various add on features here.  Implementation in add_on_features.c
 */

#define ovp_fault


#ifdef ovp_fault
void Telemetry_IRQ_VOUT_MFR_OVP_FAULT_HANDLE(Telemetry_IRQ_TYPE_t Telemetry_type);
#endif



#endif
