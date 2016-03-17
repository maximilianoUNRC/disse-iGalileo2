/*
 ============================================================================
 Name        : ejercicio6B_IOT.c
 Author      : maximiliano correa
 Version     : Clase 2
 Copyright   : Your copyright notice
 Description : Extender el programa del inciso 2 de modo que la iluminación
 de la pantalla LCD se ajuste gradualmente a la iluminación ambiente.
Nota: Usar A0 para la entrada del Light Sensor de los accesorios GROVE.
 ============================================================================
 */

#include "mraa.h"
#include "gpio.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "grove_lcd.h"
#include <math.h>

#define analog_Pin_0 0
typedef enum {FALSE=0, TRUE=1} boolean;
boolean state = FALSE;
char inputString[10];
#define REG_RED         0x04
#define REG_GREEN       0x03
#define REG_BLUE        0x02

void control_luz(float luz){
	if(luz < 100){
		grove_lcd_setPWM(REG_BLUE, 64);
	}

	if(100 <= luz && luz < 500){
		grove_lcd_setPWM(REG_BLUE, 128);
	}

	if(500 <= luz){
		grove_lcd_setPWM(REG_BLUE, 255);
	}

}


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
		float Rsensor; //Resistance of sensor in K

		mraa_result_t r = MRAA_SUCCESS;
		mraa_init();
		mraa_aio_context sensor = mraa_aio_init(analog_Pin_0);
		uint16_t adc_value = 0;

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
			 adc_value = mraa_aio_read(sensor);
			 Rsensor=(float)(1023-adc_value)*10/adc_value;
			 printf("Luz :  %.5f\n", Rsensor);
			 control_luz(Rsensor);
		}

		mraa_gpio_close(gpio_1);
		mraa_gpio_close(gpio_3);
		mraa_aio_close(sensor);
		return MRAA_SUCCESS;
}

