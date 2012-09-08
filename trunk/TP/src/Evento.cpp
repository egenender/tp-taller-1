#include "Evento.h"

Evento::Evento() {}

Evento::~Evento() {}

void Evento::manejarEvento(SDL_Event* evento) {
	switch (evento->type) {

		// Se pueden agregar mas eventos, para teclado, mouse, ventana, etc

		case SDL_QUIT:
			salir();
			break;
		default:
			break;
	}
}


void Evento::salir() {
	// virtual
}
