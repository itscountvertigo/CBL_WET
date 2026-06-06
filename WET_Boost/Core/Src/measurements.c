/*
 * measurements.c
 *
 *  Created on: May 30, 2026
 *      Author: 20223155
 */

#include "main.h"
#include <stdio.h>
#include "measurements.h"

static Measurement_t measurement = {0};;

extern UART_HandleTypeDef huart2;

#define MEASUREMENT_ALPHA 0.1f

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

	measurement.voltage = (voltage_adc_read * 3.3f) / 4095.0; //todo
	measurement.current = (current_adc_read * 3.3f) / 4095.0;

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
	//printf("test: %.2f\r\n", 1.23f);
	printf("V: %d, I: %d, P_inst: %.d, P_filt = %d\r\n",
			(int)(measurement.voltage * 100),
			(int)(measurement.current * 100),
			(int)(measurement.power_inst * 100),
			(int)(measurement.power_filtered * 100)
			);
	return measurement;

}
