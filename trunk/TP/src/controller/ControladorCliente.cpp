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

	if (keystates[SDLK_UP]) {
		revisarCambio(SALTAR);
		return;
	}

	if (keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT]) {
		revisarCambio(CAMINANDOIZQ);
		return;
	}

	if (keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT]) {
		revisarCambio(CAMINANDODER);
		return;
	}

	if (!(keystates[SDLK_LEFT] ^ keystates[SDLK_RIGHT]) && !keystates[SDLK_UP]) {
		revisarCambio(QUIETO);
		return;
	}
}

void ControladorCliente::enviarStruct(int nuevoEstado){
	structCliente_t* estructura = structCliente_crear(ID, nuevoEstado);
	Cliente *cliente = Cliente::obtenerInstancia("", 0);
	cliente->encolar_cambio(estructura);
}

void ControladorCliente::revisarCambio(int cambio){
	if (ultimoEstado != cambio){
		enviarStruct(cambio);
		ultimoEstado = cambio;
	}
}