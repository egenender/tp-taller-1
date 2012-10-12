#include "EstadoIntroduccion.h"
#include "ManejadorEstados.h"
#include "../gui/model/ManejadorEjemplo.h"
#include "../controller/GestorConfiguraciones.h"

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

	int anchoPantalla = GestorConfiguraciones::getInstance()->ObtenerAnchoPantalla();
	int altoPantalla = GestorConfiguraciones::getInstance()->ObtenerAltoPantalla();

	int altoBoton = 86;
	int anchoBoton = 86;
	botonIniciar = new Boton((anchoPantalla - anchoBoton)/2, (altoPantalla - altoBoton)/2, anchoBoton, altoBoton, new ManejadorEjemplo());
	botonIniciar->setearMensaje("Iniciar");

	int altoBarra = 25;
	barra = new BarraEstado(0,altoPantalla - altoBarra,anchoPantalla,altoBarra);
	barra->setearMensaje("Iddle");

	vistaBotonIniciar = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
			"src/gui/resources/botonIniciarClickeado.png");
	vistaBarra = new VistaBarraEstado();

	botonIniciar->agregarObservador(vistaBotonIniciar);
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
