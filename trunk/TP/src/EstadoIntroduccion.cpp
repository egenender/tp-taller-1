#include "EstadoIntroduccion.h"
#include "HojaSprites.h"
#include "ManejadorEstados.h"

EstadoIntroduccion EstadoIntroduccion::instancia;

// Introduccion del juego
EstadoIntroduccion::EstadoIntroduccion() {
    logo = NULL;
}

/** Inicializa el estado **/
void EstadoIntroduccion::iniciar() {
    // Load Simple Logo
    logo = new Animacion(new HojaSprites("src/yoshi.png", 64, 64));
}

/** Termina el estado **/
void EstadoIntroduccion::terminar() {
    if(logo) {
        delete(logo);
        logo = NULL;
    }
}

/** Actualiza el estado **/
void EstadoIntroduccion::actualizar() {

	logo->animar();

    // Aca se deberia cambiar a otro estado cuando se cumple una condicion
}

/** Dibuja el estado **/
void EstadoIntroduccion::dibujar(SDL_Surface* display) {
    if(logo) {
        logo->dibujar(display, 0,0);
    }
}

/** Devuelve la instancia del estado (Singleton) **/
EstadoIntroduccion* EstadoIntroduccion::obtenerInstancia() {
    return &instancia;
}
