/*
 * pwm.h
 *
 *  Created on: May 30, 2026
 *      Author: 20223155
 */

#ifndef PWM_H
#define PWM_H

#include "stm32f3xx_hal.h"

int PWM_Init(int freq, float duty_cycle);
void PWM_SetDutyCycle(float duty_cycle);

#endif
