/*
 * ControladorCliente.cpp
 *
 *  Created on: 14/10/2012
 *      Author: martin
 */

#include "ControladorCliente.h"

ControladorCliente::ControladorCliente(cola_t* cola, unsigned int id) {
	cola_salida = cola;
	ID = id;
	cambioReciente = false;
}

ControladorCliente::~ControladorCliente() {
	// TODO Auto-generated destructor stub
}

void ControladorCliente::manejarEvento(SDL_Event* evento){
	Uint8 *keystates = SDL_GetKeyState(NULL);

	// Podria ser mejor :P Movimiento medio choto este:
	if (keystates[SDLK_UP]) {
		//cola_encolar(cola_salida, bichodemierda+salta);
		cambioReciente = true;
	}
	if (keystates[SDLK_DOWN]) {

	}
	if (keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT]) {
		//cola_encolar(cola_salida, bichodemierda+izquierda);
		cambioReciente = true;
	}

	if (keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT]) {
		//cola_encolar(cola_salida, bichodemierda+izquierda);
		cambioReciente = true;
	}

	//TODO: en este if va a haber que agregar mas condiciones cuando se permita saltar/etc..
	if (!(keystates[SDLK_LEFT] ^ keystates[SDLK_RIGHT]) && cambioReciente) {
		//cola_encolar(cola_salida, bichodemierda+detener);
		cambioReciente = false;
	}
}
