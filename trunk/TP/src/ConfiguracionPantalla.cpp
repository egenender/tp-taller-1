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

SDL_Surface* ConfiguracionPantalla::CrearPantalla(){


	return SDL_SetVideoMode(ancho,alto, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

}

