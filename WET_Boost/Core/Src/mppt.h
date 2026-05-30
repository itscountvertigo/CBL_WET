/*
 * mppt.h
 *
 *  Created on: May 28, 2026
 *      Author: 20223155
 */


#ifndef MPPT_H
#define MPPT_H

#include <stdint.h>

typedef struct
{
    float duty_cycle;

    float step_size;

    float power_prev;

    int8_t direction;

    float duty_min;
    float duty_max;

} MPPT_Controller;

void MPPT_Init(MPPT_Controller *mppt);

void MPPT_Update(MPPT_Controller *mppt, float power_meas);

#endif
