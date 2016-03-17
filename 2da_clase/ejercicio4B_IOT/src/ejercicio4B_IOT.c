/*
 ============================================================================
 Name        : ejercicio4B_IOT.c
 Author      : maximiliano correa
 Version     :Clase 2
 Copyright   : Your copyright notice
 Description :Crear un programa que lea el sensor de temperatura y
 	 	 	 muestre el valor en la pantalla LCD.
 Nota:  Properties->C/C++ Build->Settings->Tool Settings->Cross GCC Linker->Libraries. (m)
 ============================================================================
 */

#include "mraa.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "grove_lcd.h"
#include <math.h>

#define analog_Pin_0 0
const int B=4275;                 // B value of the thermistor
const int R0 = 100000;            // R0 = 100k

char inputString[10];


void reverse(char *str, int len){
    int i=0, j=len-1, temp;
    while (i<j){
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

int intToStr(int x, char str[], int d){
    int i = 0;
    while (x){
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

void ftoa(float n, char *res, int afterpoint){
    int ipart = (int)n;
    float fpart = n - (float)ipart;
    int i = intToStr(ipart, res, 0);
    if (afterpoint != 0){
        res[i] = '.';
        fpart = fpart * pow(10,afterpoint);
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}




int main() {
	// Setup()
	mraa_init();
	mraa_aio_context sensor = mraa_aio_init(analog_Pin_0);
	uint16_t adc_value = 0;
	float adc_value_float = 0.0;

	float temperature = 0.0;

	const int colorR = 0;
	const int colorG = 0;
	const int colorB = 255;

	grove_lcd_begin(16, 2);
	grove_lcd_setRGB(colorR, colorG, colorB);


    for (;;) {
    	adc_value = mraa_aio_read(sensor);
    	adc_value_float = mraa_aio_read_float(sensor);
		float R = 1023.0/((float)adc_value)-1.0;
		R = 100000.0*R;
		temperature = 1.0/(log(R/100000.0)/B+1/298.15)-273.15;
		ftoa(temperature, inputString, 2);
		grove_lcd_clear();
		grove_lcd_home();
		grove_lcd_write((char *)&inputString);
		printf("Temperatura:  %.5f\n", temperature);
		sleep(1);
    }

    mraa_aio_close(sensor);
    return MRAA_SUCCESS;

}

