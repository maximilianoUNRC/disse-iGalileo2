/*
 ============================================================================
 Name        : ejercicio3_IOT.c
 Author      : maximiliano correa
 Version     :
 Copyright   : Your copyright notice
 Description :
 Utilizar el ejemplo de ADC dado en clase para conceptualizar el uso del conversor
 Analogico / Digital.
 Nota: Usar A0 para la entrada del Rotary Angle Sensor de los accesorios GROVE
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "mraa.h"

#define analog_Pin_0 0 // El potenciometro esta conectado al analogico_0

int main() {
	// Setup()
	mraa_init();
	mraa_aio_context pot = mraa_aio_init(analog_Pin_0);
    uint16_t adc_value = 0;
    float adc_value_float = 0.0;

    for (;;) {
        adc_value = mraa_aio_read(pot);
        adc_value_float = mraa_aio_read_float(pot);
        fprintf(stdout, "ADC A0 read %X - %d\n", adc_value, adc_value);
        fprintf(stdout, "ADC A0 read float - %.5f\n", adc_value_float);
        usleep(10000);
    }

    mraa_aio_close(pot);
    return MRAA_SUCCESS;

}

