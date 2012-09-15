#include "Camara2.h"

Camara::~Camara() {}

Camara::Camara(int x, int y) {
	cam = new SDL_Rect();
	cam->x = 0;
	cam->y = 0;
	cam->w = ANCHO_VENTANA;
	cam->h = ALTO_VENTANA;

	if (x > 0 || y > 0) {
		cam->x = x;
		cam->y = y;
	}
}

void Camara::actualizar(int x, int y, int ancho, int alto) {

	// Centramos la camara:
	cam->x = (x + ancho / 2) - ANCHO_VENTANA / 2;
	cam->y = (y + alto / 2) - ALTO_VENTANA / 2;

	// No dejo que se vaya del nivel:
	if (cam->x < 0) {
		cam->x = 0;
	}
	if (cam->y < 0) {
		cam->y = 0;
	}
	if (cam->x > ANCHO_NIVEL - cam->w) {
		cam->x = ANCHO_NIVEL - cam->w;
	}
	if (cam->y > ALTO_NIVEL - cam->h) {
		cam->y = ALTO_NIVEL - cam->h;
	}
}

int Camara::obtenerX() {
	return cam->x;
}

int Camara::obtenerY() {
	return cam->y;
}

SDL_Rect* Camara::obtenerDimensiones() {
	return cam;
}
