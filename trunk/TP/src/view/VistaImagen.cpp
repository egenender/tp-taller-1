#include "VistaImagen.h"
#include <math.h>
#include "../model/Cuerpo.h"

VistaImagen::VistaImagen() {
	movY = 0;
	alpha = 0;
	imagen = NULL;
}

VistaImagen::VistaImagen(Superficie* imagenNueva, int angulo) {
	movY = 0;
	imagen = imagenNueva;
	if (angulo < 0)
		angulo += 2;

	if (angulo > 0)
		angulo -= 2;
	alpha = angulo;
	if (imagen) {
		imagen->girar(angulo);
	}
}

VistaImagen::VistaImagen(string ID) {
//	cambiarImagen(ID);
	imagen = NULL;
	movY = 0;
	alpha = 0;
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
	posicionDibujar = observable->obtenerPosicion();
	movY = 0;
	Cuerpo* c = (Cuerpo*)observable;
	if (alpha > 0){
		float angulito = alpha * 3.1415 / 180;
		movY = c->obtenerAncho() * sin (angulito) ;
		movY += 5;
	}

}

bool VistaImagen::dibujar(SDL_Surface* display, int xCamara, int yCamara) {
	if (display == NULL || imagen == NULL || posicionDibujar == NULL)
		return false;

	return imagen->dibujar(display, posicionDibujar->obtenerX() - xCamara, posicionDibujar->obtenerY() - yCamara - movY);
}
