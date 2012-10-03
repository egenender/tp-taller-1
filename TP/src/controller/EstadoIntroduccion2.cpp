#include "EstadoIntroduccion2.h"
#include "../view/HojaSprites.h"
#include "ManejadorEstados.h"

EstadoIntroduccion2 EstadoIntroduccion2::instancia;

// Introduccion del juego
EstadoIntroduccion2::EstadoIntroduccion2() {
	camara = NULL;
	fondo = NULL;
	yoshiNormal = NULL;
	x = 0;
	y = 400;
	dx = dy =0;
	velocidadX = velocidadY = 100; // 100 pixeles por segundo
}

/** Inicializa el estado **/
void EstadoIntroduccion2::iniciar() {

	// iniciamos la camara:
	camara = new Camara(x,y);

	fondo = new Superficie("src/resources/fondoGrande.png");

	HojaSprites* normal = new HojaSprites("src/resources/yoshi.png", 64, 64);
	normal->transparencia(255, 0, 255);
	yoshiNormal = new Animacion(normal);
}

/** Termina el estado **/
void EstadoIntroduccion2::terminar() {
	if (yoshiNormal) {
		delete (yoshiNormal);
		yoshiNormal = NULL;
	}
}

/** Actualiza el estado **/
void EstadoIntroduccion2::actualizar(float delta) {
	x += dx * delta;
	y += dy * delta;

	yoshiNormal->animar();
}

/** Dibuja el estado **/
void EstadoIntroduccion2::dibujar(SDL_Surface* display) {
	SDL_Rect* dimensiones = camara->obtenerDimensiones();
	fondo->dibujar(display, 0, 0, dimensiones);
	yoshiNormal->dibujar(display, x - dimensiones->x, y - dimensiones->y);
}

/** Devuelve la instancia del estado (Singleton) **/
EstadoIntroduccion2* EstadoIntroduccion2::obtenerInstancia() {
	return &instancia;
}


/** Maneja eventos que vienen del teclado **/
void EstadoIntroduccion2::manejarEvento(SDL_Event* evento) {
	Uint8 *keystates = SDL_GetKeyState(NULL);

	// Podria ser mejor :P Movimiento medio choto este:
	if (keystates[SDLK_UP])
		dy = (velocidadY * -1);
	if (keystates[SDLK_DOWN])
		dy = velocidadY;
	if (keystates[SDLK_LEFT])
		dx = (velocidadX * -1);
	if (keystates[SDLK_RIGHT])
		dx = velocidadY;
	if (!keystates[SDLK_UP] && !keystates[SDLK_DOWN])
		dy = 0;
	if (!keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT])
		dx = 0;

	if (keystates[SDLK_2])
		ManejadorEstados::setearEstadoActual(ESTADO_INTRO2);
	if (keystates[SDLK_3])
		ManejadorEstados::setearEstadoActual(ESTADO_JUEGO);

}
