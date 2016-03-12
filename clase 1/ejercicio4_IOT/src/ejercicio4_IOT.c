/*
 ============================================================================
 Name        : ejercicio4_IOT.c
 Author      : maximiliano correa
 Version     :
 Copyright   : Your copyright notice
 Description :
Al ejercicio anterior cambiar la entrada ADC, utilizar el Sensor de Temperatura.
Nota: Tener consideración el enlace que se da en el Aula Claroline para una correcta lectura e
interpretación del Sensor.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "mraa.h"
#include "math.h"

#define analog_Pin_0 0
const int B=4275;                 // B value of the thermistor
const int R0 = 100000;            // R0 = 100k

int main() {
	// Setup()
	mraa_init();
	mraa_aio_context sensor = mraa_aio_init(analog_Pin_0);
    uint16_t adc_value = 0;
    float adc_value_float = 0.0;

    for (;;) {
        adc_value = mraa_aio_read(sensor);
        adc_value_float = mraa_aio_read_float(sensor);

        float R = 1023.0/((float)adc_value)-1.0;
        R = 100000.0*R;

        float temperature = 1.0/(log(R/100000.0)/B+1/298.15)-273.15;

        fprintf(stdout, "ADC A0 read %X - %d\n", adc_value, adc_value);
        fprintf(stdout, "ADC A0 read float - %.5f\n", adc_value_float);
        printf("Temperatura:  %.5f\n", temperature);
        usleep(10000);
    }

    mraa_aio_close(sensor);
    return MRAA_SUCCESS;

}

