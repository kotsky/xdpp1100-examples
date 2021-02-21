/*
 * custom_vdac.h
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

#ifndef SRC_USER_APP_CUSTOM_VDAC_H_
#define SRC_USER_APP_CUSTOM_VDAC_H_

void xaddr_resistance_measurement(PMBUS_PAGE_t loop);
uint16_t vdac_xaddr_measurement(PMBUS_PAGE_t loop);
void vout_command_set(PMBUS_PAGE_t loop, uint16_t vdac_xaddr);

#endif /* SRC_USER_APP_CUSTOM_VDAC_H_ */
