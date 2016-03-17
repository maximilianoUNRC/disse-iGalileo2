/*
 ============================================================================
 Name        : ejercicio2B_IOT.c
 Author      : maximiliano correa
 Version     : Clase 2
 Copyright   : Your copyright notice
 Description : Crear un programa que itere un menú cíclico de 5 opciones
 	 	 	 al apretar un pulsador. El programa debe ir mostrando las opciones
 	 	 	 (elegirlas a su criterio) en la pantalla LCD.
Nota: Usar D3 para la entrada del Button Sensor de los accesorios GROVE.
 ============================================================================
 */

#include "mraa.h"
#include "gpio.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "grove_lcd.h"

#define buttonPin_ 28
typedef enum {FALSE=0, TRUE=1} boolean;
boolean state = FALSE;
char inputString[50];

void menu(int opcion){
	switch (opcion ) {
	case 1:
		strcpy((char *)&inputString, "opcion_1");
	  break;
	case 2:
		strcpy((char *)&inputString, "opcion_2");
	  break;
	case 3:
		strcpy((char *)&inputString, "opcion_3");
		break;
	case 4:
		strcpy((char *)&inputString, "opcion_4");
		break;
	case 5:
		strcpy((char *)&inputString, "opcion_5");
		break;
	default:
		strcpy((char *)&inputString, "presione pulsador:");
	  break;
	}
	//sleep(1);
	grove_lcd_clear();
	grove_lcd_home();
	grove_lcd_write((char *)&inputString);
	return;
}


int main()
{
		mraa_result_t r = MRAA_SUCCESS;
		mraa_init();
	    mraa_gpio_context gpio_1 = mraa_gpio_init_raw(30);
		mraa_gpio_dir(gpio_1, MRAA_GPIO_OUT);
		mraa_gpio_write(gpio_1, 1);
		mraa_gpio_context gpio_3 = mraa_gpio_init_raw(18);
		mraa_gpio_dir(gpio_3, MRAA_GPIO_IN);

		const int colorR = 0;
		const int colorG = 0;
		const int colorB = 255;

		grove_lcd_begin(16, 2);
		grove_lcd_setRGB(colorR, colorG, colorB);

		int contador = 0;
		menu(contador);

		for(;;) {
			if(mraa_gpio_read(gpio_3) != 0 ){
				contador++;
				menu(contador);
				if(contador == 5){
					contador =0;
				}
			}
			sleep(1);
		}
		mraa_gpio_close(gpio_1);
		mraa_gpio_close(gpio_3);
		return r;
}

