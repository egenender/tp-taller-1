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

void Controlador::manejarEvento(SDL_Event* evento, Manual* principal) {
	if (evento->type == SDL_MOUSEMOTION || evento->type == SDL_MOUSEBUTTONDOWN
			|| evento->type == SDL_MOUSEBUTTONUP)
		return;

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

