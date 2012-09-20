#include "VistaAnimada.h"

VistaAnimada::VistaAnimada() {
	animacionActual = NULL;
	animaciones = new map<int,Animacion*>();
}

VistaAnimada::~VistaAnimada() {
	if (animaciones != NULL) {
		delete(animaciones);
		animacionActual = NULL;
		animaciones = NULL;
	}

	if (animacionActual != NULL) {
		delete(animacionActual);
		animacionActual = NULL;
	}
}

bool VistaAnimada::dibujar(SDL_Surface *display) {
	if (display == NULL || animacionActual == NULL || posicionDibujar == NULL)
		return false;

	animacionActual->animar();

	return animacionActual->dibujar(display, posicionDibujar->getX(), posicionDibujar->getY());
}
