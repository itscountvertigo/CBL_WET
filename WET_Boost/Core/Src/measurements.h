/*
 * measurements.h
 *
 *  Created on: May 28, 2026
 *      Author: 20223155
 */


#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

#include <stdint.h>

typedef struct
{
    float voltage;
    float current;

    float power_inst;
    float power_filtered;

} Measurement_t;

void Measurement_Update(uint32_t voltage_adc_read, uint32_t current_adc_read);

Measurement_t Measurement_Get(void);

#endif
