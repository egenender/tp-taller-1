#include "Aplicacion.h"
#include "ManejadorEstados.h"

/** Constructor **/
Aplicacion::Aplicacion() {
	display = NULL;
	corriendo = true;
}

/** Iniciar las cosas: **/
bool Aplicacion::iniciar() {

	// Iniciamos SDL:
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    // Creamos la ventana:
    if((display = SDL_SetVideoMode(ANCHO_VENTANA, ALTO_VENTANA, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
        return false;


    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    // Seteamos el primer estado al entrar al juego:
    ManejadorEstados::setearEstadoActual(ESTADO_INTRO);

    return true;
}

/** Manejar eventos (teclado, mouse, etc) **/
void Aplicacion::manejarEvento(SDL_Event* evento) {
	Evento::manejarEvento(evento);
	ManejadorEstados::manejarEvento(evento);
}

/** Actualizar **/
void Aplicacion::actualizar() {
	ManejadorEstados::actualizar();
}

/** Dibujar **/
void Aplicacion::dibujar() {

	// Primero limpiamos la pantalla:
	SDL_FillRect(display, NULL, SDL_MapRGB(display->format, 0, 0, 0));

	// Ahora dibujamos las cosas:
    ManejadorEstados::dibujar(display);

    // Y actualizamos:
    SDL_Flip(display);
}

/** Liberar toda la memoria **/
void Aplicacion::limpiar() {
    ManejadorEstados::setearEstadoActual(ESTADO_NINGUNO);

    SDL_FreeSurface(display);
    SDL_Quit();
}

/** Al salir de la aplicacion **/
void Aplicacion::salir() {
	corriendo = false;
}

/** Gameloop */
int Aplicacion::ejecutar() {
	if (iniciar() == false)
		return -1;

	SDL_Event evento;
	while (corriendo) {
		while (SDL_PollEvent(&evento)) {
			manejarEvento(&evento);
		}
		actualizar();
		dibujar();
		SDL_Delay(100);
	}
	limpiar();
	return 0;
}


/** Se ejecuta el programa **/
int main(int argc, char* argv[]) {
	Aplicacion aplicacion;
	return aplicacion.ejecutar();
}
