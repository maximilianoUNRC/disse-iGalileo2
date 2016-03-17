/*
 ============================================================================
 Name        : ejercicio1B_IOT.c
 Author      : maximiliano correa
 Version     : Clase 2
 Copyright   : Your copyright notice
 Description : Crear un programa que le pida al usuario que ingrese un
 	 	 	   texto y luego lo imprima en la pantalla LCD.
 ============================================================================
 */

#include "mraa.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "grove_lcd.h"

typedef enum {FALSE=0, TRUE=1} boolean;
char inputString[50];
boolean stringComplete = FALSE;

void lectura_Datos(){
	 printf ("Introduzca una cadena: ");
	 getSTR(inputString, sizeof(inputString));
	 stringComplete = TRUE;
	 return;
}

int getSTR(char *cad, int n) {
    int i, c;
    c=getchar();
    if (c == EOF) {
        cad[0] = '\0';
        return 0;
    }

    if (c == '\n')
        i = 0;
    else {
        cad[0] = c;
        i = 1;
    }

    for (; i < n-1 && (c=getchar())!=EOF && c!='\n'; i++)
       cad[i] = c;

    cad[i] = '\0';

    if (c != '\n' && c != EOF)
        while ((c = getchar()) != '\n' && c != EOF);

    return 1;
}



int main()
{
		const int colorR = 0;
		const int colorG = 0;
		const int colorB = 255;

		grove_lcd_begin(16, 2);
		grove_lcd_setRGB(colorR, colorG, colorB);

		strcpy((char *)&inputString, "Ingrese Texto");
		grove_lcd_clear();
		grove_lcd_home();
		grove_lcd_write((char *)&inputString);

		for(;;) {
			 lectura_Datos();
			 if (stringComplete) {
				 grove_lcd_clear();
				 grove_lcd_home();
				 grove_lcd_write((char *)&inputString);
			     strcpy((char *)&inputString, "");
				 stringComplete = FALSE;
			 }
		}
		return 1;
}

