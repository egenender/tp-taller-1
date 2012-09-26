#include "Controlador.h"

/*Controlador* Controlador::instancia = NULL;*/
/*
 Controlador* getInstance(){
 if (!instancia)
 instancia = new Controlador();
 return instancia;
 }

 * */

Controlador::Controlador() {

}

Controlador::~Controlador() {
	// TODO Auto-generated destructor stub
}

// NUEVO MANEJAR EVENTO
/*void Controlador::manejarEvento(SDL_Event* evento, Manual* principal) {
	Uint8 *keystates = SDL_GetKeyState(NULL);

	if (keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT]) {
		principal->moverALaIzquierda();
	}
	if (keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT]) {
		principal->moverALaDerecha();
	}
	if (!(keystates[SDLK_LEFT] ^ keystates[SDLK_RIGHT])) {
		principal->detener();
	}
}*/

// VIEJO MANEJAR EVENTO:
void Controlador::manejarEvento(SDL_Event* evento, Manual* principal) {

	Uint8 *keystates = SDL_GetKeyState(NULL);

	// Podria ser mejor :P Movimiento medio choto este:
	if (keystates[SDLK_UP]) {
		//principal->saltar(); ?
	}
	if (keystates[SDLK_DOWN]) {

	}
	if (keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT]) {
		principal->moverALaIzquierda();
	}

	if (keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT]) {
		principal->moverALaDerecha();
	}

	//TODO: en este if va a haber que agregar mas condiciones cuando se permita saltar/etc..
	if (!(keystates[SDLK_LEFT] ^ keystates[SDLK_RIGHT])) {
		principal->detener();
	}

}
