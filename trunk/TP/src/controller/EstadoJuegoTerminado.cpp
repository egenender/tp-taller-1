#include "EstadoJuegoTerminado.h"
#include "ManejadorEstados.h"
#include "GestorConfiguraciones.h"

EstadoJuegoTerminado EstadoJuegoTerminado::instancia;

EstadoJuegoTerminado::EstadoJuegoTerminado() {
	fondo = NULL;
	ganador = NULL;
}

EstadoJuegoTerminado::~EstadoJuegoTerminado() {
	// TODO Auto-generated destructor stub
}

void EstadoJuegoTerminado::manejarEvento(SDL_Event* evento){
	if ((evento->type == SDL_KEYDOWN)&& (evento->key.keysym.sym == SDLK_ESCAPE)) {
		ManejadorEstados::setearEstadoActual(ESTADO_MENU_PRINCIPAL);
	}
}

void EstadoJuegoTerminado::iniciar(){
	fondo = new Superficie("src/gui/resources/fondoPrincipal.jpg");
	fondo->escala(800,600);
	//tengo que ver como consigo al ganador-> seguro lo obtengo por el nombre ;)
	ganador = new Superficie(GestorConfiguraciones::getInstance()->rutaGanador() );
	ganador->transparencia(255,0,255);
	GestorConfiguraciones::getInstance()->acabarGestor();
}

void EstadoJuegoTerminado::terminar(){
	if (fondo){
		delete (fondo);
		fondo = NULL;
	}
	if (ganador){
		delete (ganador);
		ganador = NULL;
	}
}

void EstadoJuegoTerminado::actualizar(float delta){
	// no hay que hacer nada
}

void EstadoJuegoTerminado::dibujar(SDL_Surface* display){
	fondo->dibujar(display, 0 ,0);
	if (ganador)
		ganador->dibujar(display, 100, 100);
}

EstadoJuegoTerminado* EstadoJuegoTerminado::obtenerInstancia(){
	return &instancia;
}
