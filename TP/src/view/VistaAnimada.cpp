#include "VistaAnimada.h"

VistaAnimada::VistaAnimada() {
	animacionActual = NULL;
	animaciones = new map<int,Animacion*>();
}

VistaAnimada::~VistaAnimada() {
	if (animaciones != NULL) {
		map<int, Animacion*>::iterator iter;
		for (iter = animaciones->begin(); iter != animaciones->end(); ++iter) {
			Animacion* anim = (*iter).second;
			if (anim != NULL) {
				delete(anim);
				anim = NULL;
			}
		}
		animaciones->clear();
		delete(animaciones);
		animaciones = NULL;
	}

/*	if (animacionActual != NULL) {
		delete(animacionActual);
		animacionActual = NULL;
	}*/
}

bool VistaAnimada::dibujar(SDL_Surface *display, int xCamara, int yCamara ) {
	if (display == NULL || animacionActual == NULL || posicionDibujar == NULL)
		return false;

	animacionActual->animar();

	return animacionActual->dibujar(display, posicionDibujar->obtenerX() - xCamara, posicionDibujar->obtenerY() - yCamara);
}
