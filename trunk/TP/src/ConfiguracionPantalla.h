/*
 * ConfigPantalla.h
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */
#ifndef CONFIGPANTALLA_H
#define CONFIGPANTALLA_H
#include "Superficie.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class ConfiguracionPantalla{

	public:
		int ancho;
		int alto;
		Superficie* superficieCargada;

	public:
		ConfiguracionPantalla();
		SDL_Surface* CrearPantalla();

};

#endif
