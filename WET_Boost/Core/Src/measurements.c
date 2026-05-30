/*
 * measurements.c
 *
 *  Created on: May 30, 2026
 *      Author: 20223155
 */

#include "measurements.h"

static Measurement_t measurement;

#define MEASUREMENT_ALPHA 0.1f

void Measurement_Update(uint32_t voltage_adc_read, uint32_t current_adc_read) {

	measurement.voltage = (voltage_adc_read * 3.3f) / 4095.0;
	measurement.current = (current_adc_read * 3.3f) / 4095.0;

	measurement.power_inst = measurement.voltage * measurement.current;

	measurement.power_filtered = (MEASUREMENT_ALPHA * measurement.power_inst) +
								 ((1.0f-MEASUREMENT_ALPHA) * measurement.power_filtered);
}

Measurement_t Measurement_Get(void) {

	return measurement;

}
