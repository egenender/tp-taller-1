/*
 * ConfigPantalla.cpp
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include "ConfiguracionPantalla.h"




ConfiguracionPantalla::ConfiguracionPantalla(){

	ancho=alto=0;

}

Ventana* ConfiguracionPantalla::CrearPantalla(){
	Ventana* ventana = new Ventana(800,600);
	//Ventana* ventana = new Ventana(ancho,alto);

	return ventana;

}

