#include "VistaImagen.h"
#include "Manual.h"

VistaImagen::VistaImagen() {
	imagen = NULL;
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

bool VistaImagen::dibujar(SDL_Surface* display) {
	if (display == NULL || imagen == NULL || posicionDibujar == NULL)
		return false;

	return imagen->dibujar(display, posicionDibujar->getX(), posicionDibujar->getY());
}
