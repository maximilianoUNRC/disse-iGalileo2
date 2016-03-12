/*
 ============================================================================
 Name        : ejercicio5_IOT.c
 Author      : maximiliano correa
 Version     :
 Copyright   : Your copyright notice
 Description :
Cambiar nuevamente el Sensor para interpretar un Sensor de Luz.
Nota: Tener consideración el enlace que se da en el Aula Claroline del Sensor de Luz.
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "mraa.h"

#define analog_Pin_0 0

int main() {
	float Rsensor; //Resistance of sensor in K
	// Setup()
	mraa_init();
	mraa_aio_context sensor = mraa_aio_init(analog_Pin_0);
    uint16_t adc_value = 0;
    float adc_value_float = 0.0;

    for (;;) {
        adc_value = mraa_aio_read(sensor);
        adc_value_float = mraa_aio_read_float(sensor);

        Rsensor=(float)(1023-adc_value)*10/adc_value;

        fprintf(stdout, "ADC A0 read %X - %d\n", adc_value, adc_value);
        fprintf(stdout, "ADC A0 read float - %.5f\n", adc_value_float);
        printf("Cant Luz:  %.5f\n", Rsensor);
        usleep(10000);
    }

    mraa_aio_close(sensor);
    return MRAA_SUCCESS;

}


