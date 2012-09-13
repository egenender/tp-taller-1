#include "EstadoIntroduccion.h"
#include "HojaSprites.h"
#include "ManejadorEstados.h"

EstadoIntroduccion EstadoIntroduccion::instancia;

// Introduccion del juego
EstadoIntroduccion::EstadoIntroduccion() {
	fondo = NULL;
	yoshiNormal = NULL;
	yoshiGigante = NULL;
	espejada = NULL;
	original = NULL;
}

/** Inicializa el estado **/
void EstadoIntroduccion::iniciar() {
	fondo = new Superficie("src/fondo.jpg");

	HojaSprites* normal = new HojaSprites("src/yoshi.bmp", 64, 64);
	normal->transparencia(255, 0, 255);

	HojaSprites* gigante = new HojaSprites("src/yoshi.bmp", 64, 64);
	gigante->escala(2);
	gigante->transparencia(255, 0, 255);

	yoshiNormal = new Animacion(normal);
	yoshiGigante = new Animacion(gigante);

	original = new Superficie("src/yoshi.bmp");
	original->transparencia(255, 0, 255);

	espejada = original->voltear(HORIZONTALMENTE);
}

/** Termina el estado **/
void EstadoIntroduccion::terminar() {

	delete (yoshiNormal);
	yoshiNormal = NULL;

	delete (yoshiGigante);
	yoshiGigante = NULL;

	delete (espejada);
	espejada = NULL;

	delete (original);
	original = NULL;

	delete (fondo);
	fondo = NULL;
}

/** Actualiza el estado **/
void EstadoIntroduccion::actualizar() {

	yoshiNormal->animar();
	yoshiGigante->animar();
	// Aca se deberia cambiar a otro estado cuando se cumple una condicion
}

/** Dibuja el estado **/
void EstadoIntroduccion::dibujar(SDL_Surface* display) {

	fondo->dibujar(display, 0, 0);

	yoshiNormal->dibujar(display, 0, 0);
	yoshiNormal->dibujar(display, 32, 0);
	yoshiGigante->dibujar(display, 400, 30);
	original->dibujar(display, 200, 0);
	espejada->dibujar(display, 300, 0);

}

/** Devuelve la instancia del estado (Singleton) **/
EstadoIntroduccion* EstadoIntroduccion::obtenerInstancia() {
	return &instancia;
}
