/*
 * patch_Telemetry_get_adc_code.h
 *
 *  Created on: 3 Sep 2019
 *      Author: halimand
 */

#ifndef SRC_USER_APP_PATCH_TELEMETRY_GET_H_
#define SRC_USER_APP_PATCH_TELEMETRY_GET_H_

#include <stdint.h>

#include "../../common/modules/telemetry/telemetry_api.h"

uint16_t patch_Telemetry_get_adc_code(int16_t temp);
int32_t patch_Telemetry_get(PMBUS_PAGE_t loop, TELEMETRY_TYPE_t telem_type);

#endif /* SRC_USER_APP_PATCH_TELEMETRY_GET_H_ */
