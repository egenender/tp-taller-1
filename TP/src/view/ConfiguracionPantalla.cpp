/*
 * ConfigPantalla.cpp
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include "ConfiguracionPantalla.h"




ConfiguracionPantalla::ConfiguracionPantalla(){

	ancho=alto=0;
	superficieCargada=0;
	//superficieCargada= new Superficie();

}

Ventana* ConfiguracionPantalla::CrearPantalla(){

	Ventana* ventana = new Ventana(ancho,alto);

	return ventana;

}

