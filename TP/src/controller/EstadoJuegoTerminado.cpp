#include "EstadoJuegoTerminado.h"
#include "GestorConfiguraciones.h"
#include "../gui/model/Ventana.h"

EstadoJuegoTerminado EstadoJuegoTerminado::instancia;

EstadoJuegoTerminado::EstadoJuegoTerminado() {
	fondo = NULL;
	ganador = NULL;
	ganadores = NULL;
	timer = NULL;
	actual = 0;
	btnMenu = NULL;
	vistaMenu = NULL;
}

EstadoJuegoTerminado::~EstadoJuegoTerminado() {
}

void EstadoJuegoTerminado::manejarEvento(SDL_Event* evento){
	if ((evento->type == SDL_KEYDOWN)&& (evento->key.keysym.sym == SDLK_ESCAPE)) {
		ManejadorEstados::setearEstadoActual(ESTADO_MENU);
	}
	btnMenu->manejarEvento(evento);
}

void EstadoJuegoTerminado::iniciar(){
	fondo = new Superficie("src/gui/resources/fondoPrincipal.jpg");
	fondo->escala(ANCHO_ESTANDARD,ALTO_ESTANDARD);
	//tengo que ver como consigo al ganador-> seguro lo obtengo por el nombre ;)
	ganadores = GestorConfiguraciones::getInstance()->obtenerGanadores();
	for (unsigned int i = 0; i < ganadores->size(); i++)
		ganadores->at(i)->transparencia(255,0,255);
	ganador = ganadores->at(0);
	actual = 0;
	GestorConfiguraciones::getInstance()->acabarGestor();
	timer = new Timer();
	if (ganadores->size() > 1)
		timer->comenzar();

	btnMenu = new Boton(40,40,150,50, new ManejadorCambiaEstado(ESTADO_MENU));

	vistaMenu = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
				"src/gui/resources/botonIniciarClickeado.png");

	btnMenu->setearMensaje("Volver al Menu");
	btnMenu->agregarObservador(vistaMenu);

}

void EstadoJuegoTerminado::terminar(){
	if (fondo){
		delete (fondo);
		fondo = NULL;
	}
	if (ganadores){
		for (unsigned int i = 0; i < ganadores->size(); i++)
			delete(ganadores->at(i));
		ganadores->clear();
		delete (ganadores);
		ganadores = NULL;
		ganador = NULL;
	}
	if (timer){
		delete (timer);
		timer = NULL;
	}
	if (btnMenu){
		delete (btnMenu);
		btnMenu = NULL;
	}
	if (vistaMenu){
		delete (vistaMenu);
		vistaMenu = NULL;
	}
}

void EstadoJuegoTerminado::actualizar(float delta){
	btnMenu->actualizar();
	if (ganadores->size() == 1) return;

	if (timer->obtenerTiempo() >= (TIEMPO_GANADOR*1000)){
		actual++;
		if (actual == ganadores->size())
			actual = 0;
		ganador = ganadores->at(actual);
		timer->detener();
		timer->comenzar();
	}
}

void EstadoJuegoTerminado::dibujar(SDL_Surface* display){
	fondo->dibujar(display, 0 ,0);
	if (ganador) {
		ganador->dibujar(display, 450, 200);
	}
	vistaMenu->dibujar(display);
}

EstadoJuegoTerminado* EstadoJuegoTerminado::obtenerInstancia(){
	return &instancia;
}
