#include "ControladorCliente.h"
#include "../model/structures/structCliente.h"
#include "Cliente.h"

ControladorCliente::ControladorCliente(unsigned int id) {
	ID = id;
	ultimoEstado = QUIETO;
}

ControladorCliente::~ControladorCliente() {

}

void ControladorCliente::manejarEvento(SDL_Event* evento){
	Uint8 *keystates = SDL_GetKeyState(NULL);

	// Podria ser mejor :P Movimiento medio choto este:
	if (keystates[SDLK_UP] && ultimoEstado != SALTAR) {
		enviarStruct(SALTAR);
		ultimoEstado = SALTAR;
		return;
	}

	if (keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT] && ultimoEstado != CAMINANDOIZQ) {
		enviarStruct(CAMINANDOIZQ);
		ultimoEstado = CAMINANDOIZQ;
		return;
	}

	if (keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT] && ultimoEstado != CAMINANDODER) {
		enviarStruct(CAMINANDODER);
		ultimoEstado = CAMINANDODER;
		return;
	}

	if (!(keystates[SDLK_LEFT] ^ keystates[SDLK_RIGHT]) && ultimoEstado != QUIETO) {
		enviarStruct(QUIETO);
		ultimoEstado = QUIETO;
		return;
	}
}

void ControladorCliente::enviarStruct(int nuevoEstado){
	//structCliente_t* estructura = structCliente_crear(ID, nuevoEstado);
	/*Cliente *cliente = Cliente::obtenerInstancia();
	cliente->encolar_cambio(estructura);*/
}
