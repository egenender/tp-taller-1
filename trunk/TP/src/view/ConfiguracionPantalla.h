/*
 * ConfigPantalla.h
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */
#ifndef CONFIGPANTALLA_H
#define CONFIGPANTALLA_H
#include "../gui/model/Ventana.h"

class ConfiguracionPantalla{

	public:
		int ancho;
		int alto;

	public:
		ConfiguracionPantalla();
		Ventana* CrearPantalla();

};

#endif
