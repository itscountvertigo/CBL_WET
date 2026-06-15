/*
 * measurements.c
 *
 *  Created on: May 30, 2026
 *      Author: 20223155
 */

#include "main.h"
#include <stdio.h>
#include "measurements.h"

static Measurement_t measurement = {0};

extern UART_HandleTypeDef huart2;

#define MEASUREMENT_ALPHA 0.1f

#define VOLTAGE_DIV_SCALE 20.5

#define LA55_P_RATIO 1000
#define R_BURDEN 100
#define LA55_P_TURNS 3

#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFF);

	return ch;
}

void Measurement_Update(uint32_t voltage_adc_read, uint32_t current_adc_read) {

	measurement.voltage_adc = voltage_adc_read;
	measurement.current_adc = current_adc_read;

	measurement.voltage = (voltage_adc_read * 3.3f) / 4095.0 * VOLTAGE_DIV_SCALE;
	measurement.current = (current_adc_read * 3.3f) / 4095.0 * (LA55_P_RATIO / R_BURDEN) / LA55_P_TURNS;

//	printf("ADC_V: %d, ADC_I: %d\r\n",
//			(int)(voltage_adc_read),
//			(int)(current_adc_read)
//			);

	//printf("ADC=%lu %lu\r\n", voltage_adc_read, current_adc_read);

	measurement.power_inst = measurement.voltage * measurement.current;

	if (measurement.power_filtered == 0.0f) {
	    measurement.power_filtered = measurement.power_inst;
	} else {
	    measurement.power_filtered =
	        MEASUREMENT_ALPHA * measurement.power_inst +
	        (1.0f - MEASUREMENT_ALPHA) * measurement.power_filtered;
	}
}

Measurement_t Measurement_Get(void) {
	printf("----------------\r\nV: %.2f (%d), I: %.2f (%d),\r\n P_inst: %.2f, P_filt = %.2f \r\n",
			measurement.voltage, (int)measurement.voltage_adc,
			measurement.current, (int)measurement.current_adc,
			measurement.power_inst,
			measurement.power_filtered
			);
	return measurement;

}
