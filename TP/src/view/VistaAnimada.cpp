#include "VistaAnimada.h"

VistaAnimada::VistaAnimada() {
	animacionActual = NULL;
	animaciones = new map<int,Animacion*>();
	pararDeDibujar = false;
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

void VistaAnimada::actualizar(Observable* observable) {
	VistaCuerpo::actualizar(observable);
}

bool VistaAnimada::dibujar(SDL_Surface *display, int xCamara, int yCamara, bool debug ) {
	if (pararDeDibujar) return true;
	if (display == NULL || animacionActual == NULL || posicionDibujar == NULL || posicionColision == NULL)
		return false;

	animacionActual->animar();

	bool dibuje = animacionActual->dibujar(display, posicionDibujar->obtenerX() - xCamara, posicionDibujar->obtenerY() - yCamara);

	if (debug && supDebug) {
		supDebug->dibujar(display, posicionColision->obtenerX() - xCamara, posicionColision->obtenerY() - yCamara);
	}

	return dibuje;
}
