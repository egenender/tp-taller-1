#include "EstadoIntroduccion.h"
#include "HojaSprites.h"
#include "ManejadorEstados.h"

EstadoIntroduccion EstadoIntroduccion::instancia;

// Introduccion del juego
EstadoIntroduccion::EstadoIntroduccion() {
	yoshiNormal = NULL;
	yoshiGigante = NULL;
	espejada = NULL;
	original = NULL;
}

/** Inicializa el estado **/
void EstadoIntroduccion::iniciar() {
	// Load Simple Logo
	yoshiNormal = new Animacion(new HojaSprites("src/yoshi.png", 64, 64));
	HojaSprites* gigante = new HojaSprites("src/yoshi.png", 64, 64);
	gigante->escala(2);
	//HojaSprites* espejado = gigante->espejar();
	yoshiGigante = new Animacion(gigante);

	original = new Superficie("src/yoshi.png");
	espejada = original->voltear(HORIZONTALMENTE);
}

/** Termina el estado **/
void EstadoIntroduccion::terminar() {
	if (yoshiNormal) {
		delete (yoshiNormal);
		yoshiNormal = NULL;
	}

	if (yoshiGigante) {
		delete (yoshiGigante);
		yoshiGigante = NULL;
	}

	if (espejada) {
		delete (espejada);
		espejada = NULL;
	}

	if (original) {
		delete (original);
		original = NULL;
	}
}

/** Actualiza el estado **/
void EstadoIntroduccion::actualizar() {

	yoshiNormal->animar();
	yoshiGigante->animar();
	// Aca se deberia cambiar a otro estado cuando se cumple una condicion
}

/** Dibuja el estado **/
void EstadoIntroduccion::dibujar(SDL_Surface* display) {
	if (yoshiNormal) {
		yoshiNormal->dibujar(display, 0, 0);
	}

	if (yoshiNormal) {
		yoshiNormal->dibujar(display, 32, 0);
	}

	if (yoshiGigante) {
		yoshiGigante->dibujar(display, 400, 30);
	}

	if (original) {
		original->dibujar(display, 200, 0);
	}
	if (espejada) {
		espejada->dibujar(display, 300, 0);
	}
}

/** Devuelve la instancia del estado (Singleton) **/
EstadoIntroduccion* EstadoIntroduccion::obtenerInstancia() {
	return &instancia;
}
