#include "Camara.h"
#include "Cuerpo.h"

/*Camara::Camara() {
	camara = new SDL_Rect();
	camara->x = 0;
	camara->y = 0;
	camara->w = ANCHO_VENTANA;
	camara->h = ALTO_VENTANA;
}

Camara::~Camara() {}

Camara::Camara(int x, int y) {
	Camara();

	if (x > 0 || y > 0) {
		camara->x = x;
		camara->y = y;
	}
}

void Camara::actualizar(Observable* observable) {

	Cuerpo* observado = (Cuerpo*) observable;
	Posicion* pos = observado->obtenerPosicion();

	// Centramos la camara:
	camara->x = (pos->getX() + observado->obtenerAncho() / 2) - ANCHO_VENTANA / 2;
	camara->y = (pos->getY() + observado->obtenerAlto() / 2) - ALTO_VENTANA / 2;

	// No dejo que se vaya del nivel:
	if (camara->x < 0) {
		camara->x = 0;
	}
	if (camara->y < 0) {
		camara->y = 0;
	}
	if (camara->x > ANCHO_NIVEL 0- camara->w) {
		camara->x = ANCHO_NIVEL 0- camara->w;
	}
	if (camara->y > ALTO_NIVEL 0- camara->h) {
		camara->y = ALTO_NIVEL 0- camara->h;
	}
}

int Camara::obtenerX() {
	return camara->x;
}

int Camara::obtenerY() {
	return camara->y;
}

Posicion* Camara::obtenerPosicion() {
	return new Posicion(camara->x, camara->y);
}

SDL_Rect* Camara::obtenerDimensiones() {
	return camara;
}
*/
