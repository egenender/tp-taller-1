#include "Camara.h"
#include "Cuerpo.h"

void Camara::iniciarCamara() {
	// TODO: En realidad deberia cargar la configuracion del juego, pedirsela a alguien:
	/* camara->w = Configuracion::getInstance()->obtenerAnchoVentana();
	 * camara->h = Configuracion::getInstance()->obtenerAltoVentana();
	 *
	 * anchoNivel = Configuracion::getInstance()->obtenerAnchoNivel();
	 * altoNivel = Configuracion::getInstance()->obtenerAltoNivel();
	 * imagen = ResourcesManager::getInstance()->obtenerImagen("fondoNivel");
	 */

	anchoNivel = ANCHO_NIVEL;
	altoNivel = ALTO_NIVEL;
	margenScroll = MARGEN_SCROLL;
	imagen = new Superficie("src/fondoGrande.png"); // el fondo

	camara = new SDL_Rect();
	camara->x = 0;
	camara->y = 0;
	camara->w = ANCHO_VENTANA;
	camara->h = ALTO_VENTANA;
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
	int x = observado->obtenerPosicion()->getX();
	int y = observado->obtenerPosicion()->getY();
	int ancho = observado->obtenerAncho();
	int alto = observado->obtenerAlto();

	// Centramos la camara:
	if ( (x + ancho / 2) < camara->x + margenScroll) {
		camara->x = (x + ancho / 2) - margenScroll;
	}

	if ( (x + ancho / 2) > camara->x + ANCHO_VENTANA - margenScroll) {
			camara->x = (x + ancho / 2) + margenScroll - ANCHO_VENTANA;
	}

	camara->y = (y + alto / 2) - ALTO_VENTANA / 2;


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

