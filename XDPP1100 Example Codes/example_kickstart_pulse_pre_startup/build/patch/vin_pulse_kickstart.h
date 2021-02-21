/*
 * vin_pulse_kickstart.h
 *
 *  Created on: 15 Jul 2019
 *      Author: halimand
 */

#ifndef SRC_USER_APP_VIN_PULSE_KICKSTART_H_
#define SRC_USER_APP_VIN_PULSE_KICKSTART_H_

#include <stdint.h>

extern uint8_t status;
extern uint32_t registerRead;
void force_PID_dutycycle(PMBUS_PAGE_t loop, uint32_t duty);
void pulse_kickstart(PMBUS_PAGE_t loop, uint16_t pulse_width_ns, uint16_t freq_khz);
void release_PID_dutycycle(PMBUS_PAGE_t loop);

void force_feedforward(PMBUS_PAGE_t loop);
void release_feedforward(PMBUS_PAGE_t loop);

#endif /* SRC_USER_APP_VIN_PULSE_KICKSTART_H_ */
