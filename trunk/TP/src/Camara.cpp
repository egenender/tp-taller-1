#include "Camara.h"
#include "Cuerpo.h"
#include "GestorConfiguraciones.h"

void Camara::iniciarCamara() {

	GestorConfiguraciones* gestor=GestorConfiguraciones::getInstance();

	anchoNivel = gestor->ObtenerAnchoNivel();
	altoNivel = gestor->ObtenerAltoNivel();
	margenScroll = gestor->ObtenerMargenScroll();
	imagen = gestor->ObtenerFondo();

	imagen->escala(gestor->ObtenerAnchoNivel(), gestor->ObtenerAltoNivel());

	camara = new SDL_Rect();
	camara->x = 0;
	camara->y = 0;
	camara->w = gestor->ObtenerAnchoPantalla();
	camara->h = gestor->ObtenerAltoPantalla();
}

Camara::~Camara() {}

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

	if (display == NULL)
		return false;

	imagen->dibujar(display, 0, 0, camara); // 0,0 porque lo dibujamos el fondo nomas!

	return true;
}

void Camara::actualizar(Observable* observable) {

	Cuerpo* observado = (Cuerpo*) observable;
	int x = observado->obtenerPosicion()->obtenerX();
	int y = observado->obtenerPosicion()->obtenerY();
	int ancho = observado->obtenerAncho();
	int alto = observado->obtenerAlto();

	// Centramos la camara:
	if ( (x + ancho / 2) < camara->x + margenScroll) {
		camara->x = (x + ancho / 2) - margenScroll;
	}

	if ( (x + ancho / 2) > camara->x + camara->w - margenScroll) {
			camara->x = (x + ancho / 2) + margenScroll - camara->w;
	}

	camara->y = (y + alto / 2) - camara->h / 2;


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

