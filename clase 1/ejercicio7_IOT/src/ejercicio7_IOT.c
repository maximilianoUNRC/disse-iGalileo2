/*
 ============================================================================
 Name        : ejercicio7_IOT.c
 Author      : maximiliano correa
 Version     :
 Copyright   : Your copyright notice
 Description : realizar la manipulación del Servo con el Rotary Angle Sensor.
 ============================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include "mraa.h"

#define analog_Pin_0 0 // El potenciometro esta conectado al analogico_0


int main()
{
		mraa_init();
		mraa_aio_context pot = mraa_aio_init(analog_Pin_0);
		float adc_value_float = 0.0;

		mraa_pwm_context pwm;
	    pwm = mraa_pwm_init(3);

	    mraa_pwm_period_ms(pwm, 10);
	    mraa_pwm_write(pwm, 0.0);
        mraa_pwm_enable(pwm, 1);

	    for(;;)
	    {
	    	adc_value_float = mraa_aio_read_float(pot);
	    	mraa_pwm_write(pwm, adc_value_float);
	    	usleep(100000);
	    }

	    /* disable PWM output and clean up */
        mraa_pwm_enable(pwm, 0);
        mraa_pwm_close(pwm);
	    return MRAA_SUCCESS;

}
