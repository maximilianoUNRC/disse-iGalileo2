/*
 ============================================================================
 Name        : ejercicio2_IOT.c
 Author      : maximiliano correa
 Version     :
 Copyright   : Your copyright notice
 Description :
  Al apretar el pulsador si el Led esta apagado, se debe prender;
  caso contrario, si el Led esta prendido, se debe apagar.
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "mraa.h"
#include "gpio.h"

#define ledPIN_ 3
#define buttonPin_ 28
typedef enum {FALSE=0, TRUE=1} booleano;
booleano state = FALSE;

int main() {

	mraa_result_t r = MRAA_SUCCESS;
	mraa_init();

	// Inicializacion de variables...
	mraa_gpio_context gpio_2 = mraa_gpio_init_raw(buttonPin_);
	mraa_gpio_dir(gpio_2, MRAA_GPIO_IN);

	mraa_gpio_context gpio = mraa_gpio_init_raw(ledPIN_);
    mraa_gpio_dir(gpio, MRAA_GPIO_OUT);

    //----------------------------------------------------------


	for (;;) {
		if(mraa_gpio_read(gpio_2) != 0 ){
			state = !state;
			mraa_gpio_write(gpio, state);
		}
		sleep(0.5);
	}

	mraa_gpio_close(gpio);
	mraa_gpio_close(gpio_2);
	return r;

}
