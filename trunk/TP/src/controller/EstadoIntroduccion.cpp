#include "EstadoIntroduccion.h"
#include "ManejadorEstados.h"

EstadoIntroduccion EstadoIntroduccion::instancia;

// Introduccion del juego
EstadoIntroduccion::EstadoIntroduccion() {
	botonIniciar = NULL;
	vistaBotonIniciar = NULL;
	barra = NULL;
	vistaBarra = NULL;
}

/** Inicializa el estado **/
void EstadoIntroduccion::iniciar() {

	botonIniciar = new Boton(0, 0, 86, 86);
	vistaBotonIniciar = new VistaBoton("src/botonIniciarNormal.png",
			"src/botonIniciarClickeado.png");

	botonIniciar->agregarObservador(vistaBotonIniciar);

	barra = new BarraEstado(0,200, 200,25);
	vistaBarra = new VistaBarraEstado();

	barra->setearMensaje("Iddle");

	barra->agregarObservador(vistaBarra);
}

/** Termina el estado **/
void EstadoIntroduccion::terminar() {
	if (botonIniciar) {
		delete (botonIniciar);
		botonIniciar = NULL;
	}
	if (vistaBotonIniciar) {
		delete (vistaBotonIniciar);
		vistaBotonIniciar = NULL;
	}

	if (barra) {
		delete (barra);
		barra = NULL;
	}
	if (vistaBarra) {
		delete (vistaBarra);
		vistaBarra = NULL;
	}
}

/** Actualiza el estado **/
void EstadoIntroduccion::actualizar(float delta) {
	botonIniciar->actualizar();
	barra->actualizar();

	if(botonIniciar->mouseEncima()) {
		barra->setearMensaje("Mouse encima");
	}

	else {
		barra->setearMensaje("Iddle");
	}

	if(botonIniciar->esClickeado()) {
		ManejadorEstados::setearEstadoActual(ESTADO_JUEGO);
	}
}

/** Dibuja el estado **/
void EstadoIntroduccion::dibujar(SDL_Surface* display) {
	vistaBotonIniciar->dibujar(display);
	vistaBarra->dibujar(display);

	if (botonIniciar->esClickeado())
		printf("CLICK!\n");
}

/** Devuelve la instancia del estado (Singleton) **/
EstadoIntroduccion* EstadoIntroduccion::obtenerInstancia() {
	return &instancia;
}

/** Maneja eventos que vienen del teclado **/
void EstadoIntroduccion::manejarEvento(SDL_Event* evento) {
	botonIniciar->manejarEvento(evento);
}
