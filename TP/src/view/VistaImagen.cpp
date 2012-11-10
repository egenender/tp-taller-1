#include "VistaImagen.h"

VistaImagen::VistaImagen() {
	imagen = NULL;
}

VistaImagen::VistaImagen(Superficie* imagenNueva, int angulo) {
	imagen = imagenNueva;
	if (imagen) {
		imagen->girar(angulo);
	}
}

VistaImagen::VistaImagen(string ID) {
//	cambiarImagen(ID);
	imagen = NULL;
}

VistaImagen::~VistaImagen() {
	if (imagen != NULL) {
		delete(imagen);
		imagen = NULL;
	}
}


/*void VistaImagen::cambiarImagen(string ID) {
	imagen = ResourcesManager::obtenerInstancia()->obtenerSuperficie(ID);
}*/

void VistaImagen::cambiarImagen(Superficie* imagenNueva) {
	imagen = imagenNueva;
}

void VistaImagen::actualizar(Observable* observable) {
	VistaCuerpo::actualizar(observable);
}

bool VistaImagen::dibujar(SDL_Surface* display, int xCamara, int yCamara, bool debug) {
	if (display == NULL || imagen == NULL || posicionDibujar == NULL)
		return false;

	bool dibuje = imagen->dibujar(display, posicionDibujar->obtenerX() - xCamara, posicionDibujar->obtenerY() - yCamara);

	if (debug && supDebug) {
		supDebug->dibujar(display, posicionColision->obtenerX() - xCamara, posicionColision->obtenerY() - yCamara);
	}

	return dibuje;
}
