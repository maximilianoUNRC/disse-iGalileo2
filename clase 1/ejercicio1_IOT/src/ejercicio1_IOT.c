/*
 ============================================================================
 Name        : ejercicio1_IOT.c
 Author      : maximiliano correa
 Version     :
 Copyright   : Your copyright notice
 Description :   Crear un programa que prenda un led.
 ============================================================================
 */

#include "mraa.h"
#include <stdio.h>
#include <unistd.h>
#include "gpio.h"

#define ledPIN_ 3
typedef enum {FALSE=0, TRUE=1} booleano;
booleano state = FALSE;

int main()
{
	mraa_init();
	mraa_gpio_context gpio = mraa_gpio_init_raw(ledPIN_);
    mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
	for (;;) {
		state = !state;
		mraa_gpio_write(gpio, state);
		sleep(1);
	}
	mraa_gpio_close(gpio);
	return MRAA_SUCCESS;
}
