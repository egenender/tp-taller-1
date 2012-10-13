#include "EstadoIntroduccion.h"
#include "ManejadorEstados.h"
#include "../gui/model/ManejadorEjemplo.h"
#include "../controller/GestorConfiguraciones.h"

EstadoIntroduccion EstadoIntroduccion::instancia;

// Introduccion del juego
EstadoIntroduccion::EstadoIntroduccion() {
	botonIniciar = NULL;
	vistaBotonIniciar = NULL;
	vistaBotonSacaCuadro = NULL;
	botonSacaCuadro = NULL;
	barra = NULL;
	vistaBarra = NULL;
	cuadroTexto = NULL;
	vistaCuadroTexto = NULL;
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

	int altoCuadro = 25;
	int anchoCuadro = 150;
	int cantMaxCaracteres = 10;
	cuadroTexto = new CuadroTexto((anchoPantalla - anchoCuadro)/2, altoPantalla/4, anchoCuadro, altoCuadro, cantMaxCaracteres);

	lista_t* listita = lista_crear();
	lista_insertar_primero(listita, cuadroTexto);
	ManejadorSolapa* manejador = new ManejadorSolapa(listita,lista_crear());
	botonSacaCuadro = new Boton(100, 100, anchoBoton, altoBoton, manejador);
	botonSacaCuadro->setearMensaje("Esconder");

	vistaBotonIniciar = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
			"src/gui/resources/botonIniciarClickeado.png");

	vistaBotonSacaCuadro = new VistaBoton("src/gui/resources/botonIniciarNormal.png",
				"src/gui/resources/botonIniciarClickeado.png");

	vistaBarra = new VistaBarraEstado();
	vistaCuadroTexto = new VistaCuadroTexto();

	botonSacaCuadro->agregarObservador(vistaBotonSacaCuadro);
	botonIniciar->agregarObservador(vistaBotonIniciar);
	barra->agregarObservador(vistaBarra);
	cuadroTexto->agregarObservador(vistaCuadroTexto);
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
	if (cuadroTexto) {
		delete(cuadroTexto);
		cuadroTexto = NULL;
	}
	if (vistaCuadroTexto) {
		delete(vistaCuadroTexto);
		vistaCuadroTexto = NULL;
	}
	if (botonSacaCuadro) {
		delete (botonSacaCuadro);
		botonSacaCuadro = NULL;
	}
	if (vistaBotonSacaCuadro) {
		delete (vistaBotonSacaCuadro);
		vistaBotonSacaCuadro = NULL;
	}
}

/** Actualiza el estado **/
void EstadoIntroduccion::actualizar(float delta) {
	botonIniciar->actualizar();
	barra->actualizar();
	cuadroTexto->actualizar();
	botonSacaCuadro->actualizar();


	// TODO: ESTO NO SE SI SE DEBERIA HACER ACA!
	if(botonIniciar->mouseEstaEncima()) {
		barra->setearMensaje("Mouse encima");
	}

	else {
		barra->setearMensaje("Iddle");
	}

	// TODO: esto idem, se tendria que hacer de otra forma
	if(botonIniciar->esClickeado()) {
		ManejadorEstados::setearEstadoActual(ESTADO_JUEGO);
	}
}

/** Dibuja el estado **/
void EstadoIntroduccion::dibujar(SDL_Surface* display) {
	vistaBotonIniciar->dibujar(display);
	vistaBarra->dibujar(display);
	vistaCuadroTexto->dibujar(display);
	vistaBotonSacaCuadro->dibujar(display);
}

/** Devuelve la instancia del estado (Singleton) **/
EstadoIntroduccion* EstadoIntroduccion::obtenerInstancia() {
	return &instancia;
}

/** Maneja eventos que vienen del teclado **/
void EstadoIntroduccion::manejarEvento(SDL_Event* evento) {
	botonSacaCuadro->manejarEvento(evento);
	botonIniciar->manejarEvento(evento);
	cuadroTexto->manejarEvento(evento);
}
