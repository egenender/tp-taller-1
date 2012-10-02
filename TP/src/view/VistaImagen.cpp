#include "VistaImagen.h"
#include "../model/Manual.h"

VistaImagen::VistaImagen() {
	imagen = NULL;
}

VistaImagen::VistaImagen(Superficie* imagenNueva) {
	imagen = imagenNueva;
}

VistaImagen::VistaImagen(string ID) {
//	cambiarImagen(ID);
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
	Manual* cuerpo = (Manual*) observable;
	posicionDibujar = cuerpo->obtenerPosicion();
}

bool VistaImagen::dibujar(SDL_Surface* display, int xCamara, int yCamara) {
	if (display == NULL || imagen == NULL || posicionDibujar == NULL)
		return false;

	return imagen->dibujar(display, posicionDibujar->obtenerX() - xCamara, posicionDibujar->obtenerY() - yCamara);
}