/*
 * hello_world.c
 *
 *  Created on: 11 Sep 2020
 *      Author: seetweireniv
 */

#include "shasta_hal_vsen.h"
#include "shasta_hal_vcontrol.h"
#include "shasta_hal_pwm.h"
#include "shasta_hal_pid.h"
#include "shasta_hal_scu.h"
#include "shasta_hal_cgu.h"
#include "shasta_hal_rgu.h"
#include "shasta_hal_telem.h"
#include "shasta_hal_common.h"
#include "shasta_hal_fault.h"
#include "shasta_hal_isen.h"
#include "uart_drv.h"                // uart driver functions
#include "hello_world.h"


/**
 * Hello World Example
 * Function to configure UART pin, setting and send a Hello World string.
 */
void hello_world(void)
{
	char userstring[] = "Hello World";
	ARM_DRIVER_USART * UARTdriver;
	int32_t control;

#ifdef Q040
	// MP_FUNC1 [20:18] fault1_func[2:0] 	: 6 - UARTRXD
	// MP_FUNC1 [21] 	fault1_pd 			: 0 - pulldown disabled
	// MP_FUNC1 [22] 	fault1_pu_n			: 0 - pullup enabled
	// MP_FUNC1 [23] 	fault1_ppen			: 0 - open drain output
	// MP_FUNC1 [26:24] fault2_func			: 6 - UARTTXD
	// MP_FUNC1 [27] 	fault2_pd 			: 0 - pulldown disabled
	// MP_FUNC1 [28] 	fault2_pu_n			: 0 - pullup enabled
	// MP_FUNC1 [29] 	fault2_ppen			: 1 - CMOS output
	// Refer to Register Map documentation for more detail: MP_FUNC1
	// Set Pin 1 and Pin 4 for UART (40pins)
	COMMON_MP_FUNC1__SET(0x26180000);

#else
	// MP_FUNC3 [26:24] pwm5_func[2:0] 		: 4 - UARTRXD
	// MP_FUNC3 [27] 	pwm5_pd 			: 0 - pulldown disabled
	// MP_FUNC3 [28] 	pwm5_pu_n			: 0 - pullup enabled
	// MP_FUNC3 [29] 	pwm5_ppen			: 0 - open drain output
	COMMON_MP_FUNC3__SET(0X04000000);

	// MP_FUNC4 [2:0] pwm6_func[2:0] 		: 4 - UARTXD
	// MP_FUNC4 [3] 	pwm6_pd 			: 0 - pulldown disabled
	// MP_FUNC4 [4] 	pwm6_pu_n			: 0 - pullup enabled
	// MP_FUNC4 [5] 	pwm6_ppen			: 1 - CMOS output
	COMMON_MP_FUNC4__SET(0X00000024);

#endif
	UARTdriver = &Driver_UART;
	UARTdriver->Initialize(NULL);
	UARTdriver->PowerControl (POWER_FULL);

	control = ARM_USART_MODE_ASYNCHRONOUS | ARM_USART_DATA_BITS_8 | ARM_USART_PARITY_NONE |
				ARM_USART_STOP_BITS_1 | ARM_USART_FLOW_CONTROL_NONE | ARM_USART_TXIFLSEL_7_8;

	UARTdriver->Control (control, 115200);
	UARTdriver->Control (ARM_USART_CONTROL_TX,1);
	UARTdriver->Control (ARM_USART_CONTROL_RX,1);

	UARTdriver->Send(&userstring, 11);
}

