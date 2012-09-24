#include "VistaAnimada.h"

VistaAnimada::VistaAnimada() {
	animacionActual = NULL;
	animaciones = new map<int,Animacion*>();
}

VistaAnimada::~VistaAnimada() {

	// TODO: tendriamos que eliminar las animaciones del mapa?

	/*	map<int, Animacion*>::iterator iter;
		for (iter = animaciones->begin(); iter != animaciones->end(); iter++) {
			delete(iter->second);
		}*/


	if (animaciones != NULL) {
		delete(animaciones);
//		animacionActual = NULL;
		animaciones = NULL;
	}

	if (animacionActual != NULL) {
		delete(animacionActual);
		animacionActual = NULL;
	}
}

bool VistaAnimada::dibujar(SDL_Surface *display, int xCamara, int yCamara ) {
	if (display == NULL || animacionActual == NULL || posicionDibujar == NULL)
		return false;

	animacionActual->animar();

	return animacionActual->dibujar(display, posicionDibujar->obtenerX() - xCamara, posicionDibujar->obtenerY() - yCamara);
}
