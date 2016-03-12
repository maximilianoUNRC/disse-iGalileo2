/*
 ============================================================================
 Name        : ejercicio6_IOT.c
 Author      : maximiliano correa
 Version     :
 Copyright   : Your copyright notice
 Description :  Utilizar el ejemplo de PWM para comprender el comportamiento de un Servo.
 ============================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include "mraa.h"
int main()
{
	/* initialize MRAA */
	mraa_init();
	mraa_pwm_context m_pwm = mraa_pwm_init(3);
	mraa_pwm_period_ms(m_pwm, 10);
	mraa_pwm_write(m_pwm, 0.0);
	mraa_pwm_enable(m_pwm, 1);
	int i;
	float duty = 0.0;
	for (i=0; i<10; i++)
	{

		for (duty= 0.0; duty < 1.0; duty+=0.1)
		{
			mraa_pwm_write(m_pwm, duty);
			usleep(100000);
		}
		sleep(1);
		for (duty= 1.0; duty > 0.0; duty-=0.1)
		{
			mraa_pwm_write(m_pwm, duty);
			usleep(100000);
		}
		sleep(1);
	}

	mraa_pwm_enable(m_pwm, 0);
	mraa_pwm_close(m_pwm);
	return(0);
}
