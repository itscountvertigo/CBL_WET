/*
 * mppt.c
 *
 *  Created on: May 28, 2026
 *      Author: 20223155
 */

#include "mppt.h"


void MPPT_Init(MPPT_Controller *mppt)
{
    mppt->duty_cycle = 0.50f;

    mppt->step_size = 0.005f;

    mppt->power_prev = 0.0f;

    mppt->direction = 1;

    mppt->duty_min = 0.05f;
    mppt->duty_max = 0.90f;
}

void MPPT_Update(MPPT_Controller *mppt, float power_meas) {
    // Reverse direction if power decreased
    if(power_meas < mppt->power_prev)
    {
        mppt->direction *= -1;
    }

    // Update duty
    mppt->duty_cycle += mppt->direction * mppt->step_size;

    // Clamp duty cycle
    if(mppt->duty_cycle > mppt->duty_max)
    {
        mppt->duty_cycle = mppt->duty_max;
    }

    if(mppt->duty_cycle < mppt->duty_min)
    {
        mppt->duty_cycle = mppt->duty_min;
    }

    // Store previous power
    mppt->power_prev = power_meas;

    return mppt->duty_cycle;
}


//int mppt(float power_meas, float power_prev, int prev_dir, ) {
//
//	if (power_meas >= power_prev) {
//			  if (prev_dir > 0) {
//				  duty_cycle = duty_cycle + delta_magnitude;
//				  delta = delta_magnitude;
//			  } else {
//				  duty_cycle = duty_cycle - delta_magnitude;
//				  delta = delta_magnitude * -1;
//			  }
//		  } else {		// power_meas < power_prev
//			  if (prev_dir > 0) {
//				  duty_cycle = duty_cycle - delta_magnitude;
//				  delta = delta_magnitude * -1;
//			  } else {
//				  duty_cycle = duty_cycle + delta_magnitude;
//				  delta = delta_magnitude;
//			  }
//		  }
//}
