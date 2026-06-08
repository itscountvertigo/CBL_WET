/*
 * update_pwm.c
 *
 *  Created on: May 28, 2026
 *      Author: 20223155
 */

#include "pwm.h"
#include <math.h>

extern TIM_HandleTypeDef htim1;

static int ARR;

#define TIMER_CLK 8000000.0f

int PWM_Init(int freq, float duty_cycle) {

	ARR = (int)roundf(TIMER_CLK / freq - 1);

	__HAL_TIM_SET_PRESCALER(&htim1, 0);											// PSC
	__HAL_TIM_SET_AUTORELOAD(&htim1, ARR);										// ARR

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, round((ARR+1) * duty_cycle));	// CCR1, (duty cycle = CCR1/(ARR+1) )

	HAL_TIM_GenerateEvent(&htim1, TIM_EVENTSOURCE_UPDATE);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

	__HAL_TIM_MOE_ENABLE(&htim1);

	// f_PWM = 8MHz/((PSC+1)(ARR+1))
	// The PWM is started at 100kHz with 50% duty cycle

	return 0;
}

void PWM_SetDutyCycle(float duty_cycle) {

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (int)roundf((ARR+1) * duty_cycle));	// CCR1, (duty cycle = CCR1/(ARR+1) )

//	printf("Duty cycle = %d\r\n", (int)(duty_cycle*100));
}
