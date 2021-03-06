#include "Camara.h"
#include "../model/Personajes/Manual.h"
#include "../controller/GestorConfiguraciones.h" //FIXME
#include "../gui/model/Ventana.h"

void Camara::iniciarCamara() {

	GestorConfiguraciones* gestor=GestorConfiguraciones::getInstance();

	anchoNivel = gestor->ObtenerAnchoNivel();
	altoNivel = gestor->ObtenerAltoNivel();
	margenScroll = gestor->ObtenerMargenScroll();
	margenScrollY = gestor->ObtenerMargenScrollY();
	imagen = gestor->ObtenerFondo();

	imagen->escala(gestor->ObtenerAnchoNivel(), gestor->ObtenerAltoNivel());

	camara = new SDL_Rect();
	camara->x = 0;
	camara->y = 0;
	camara->w = ANCHO_ESTANDARD;
	camara->h = ALTO_ESTANDARD;
}

Camara::~Camara() {
	if (imagen) {
		delete(imagen);
		imagen = NULL;
	}

	if (camara) {
		delete(camara);
		camara = NULL;
	}
}

Camara::Camara(int x, int y) {
	iniciarCamara();

	if (x > 0 || y > 0) {
		camara->x = x;
		camara->y = y;
	}
}

bool Camara::dibujar(SDL_Surface* display, int xCamara, int yCamara) {
	// TODO: deberia preguntarle el fondo a nivel? o lo tiene el?
	// Por ahora lo dejo como que lo tiene el:

	if (display == NULL || imagen == NULL)
		return false;

	return imagen->dibujar(display, 0, 0, camara); // 0,0 porque lo dibujamos el fondo nomas!
}

void Camara::actualizar(Observable* observable) {

	int x = observable->obtenerPosicion()->obtenerX();
	int y = observable->obtenerPosicion()->obtenerY();
	int ancho = observable->obtenerAncho();
	int alto = observable->obtenerAlto();

	// Centramos la camara:
	if ( (x ) < camara->x + margenScroll) {
		camara->x = (x) - margenScroll;
	}

	if ( (x + ancho) > camara->x + camara->w - margenScroll) {
			camara->x = (x + ancho ) + margenScroll - camara->w;
	}

	if ( (y ) < camara->y + margenScrollY) {
		camara->y = (y) - margenScrollY;
	}

	if ( (y + alto) > camara->y + camara->h - margenScrollY) {
			camara->y = (y + alto ) + margenScrollY - camara->h;
	}

	// No dejo que se vaya del nivel:
	if (camara->x < 0) {
		camara->x = 0;
	}
	if (camara->y < 0) {
		camara->y = 0;
	}
	if (camara->x > anchoNivel - camara->w) {
		camara->x = anchoNivel - camara->w;
	}
	if (camara->y > altoNivel - camara->h) {
		camara->y = altoNivel - camara->h;
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

