#include "EstadoMenuPrincipal.h"
#include "../gui/model/ManejadorEjemplo.h"
#include "ManejadorEstados.h"
#include "../gui/model/ManejadorCambiaEstado.h"

EstadoMenuPrincipal EstadoMenuPrincipal::instancia;

EstadoMenuPrincipal::EstadoMenuPrincipal() {
	fondo = NULL;
	btnMultiPlayer = btnSinglePlayer = NULL;
	animacion = NULL;
	vistaBtnMulti = vistaBtnSingle = NULL;
}

EstadoMenuPrincipal::~EstadoMenuPrincipal() {
	terminar();
}

EstadoMenuPrincipal* EstadoMenuPrincipal::obtenerInstancia() {
	return &instancia;
}

void EstadoMenuPrincipal::iniciar(){
	crearBtns();
	crearVistas();
}

void EstadoMenuPrincipal::crearBtns(){
	btnMultiPlayer = new Boton(100,400,200,40, new ManejadorCambiaEstado(ESTADO_GUI));
	btnMultiPlayer->setearMensaje("Multijugador en red");
	btnSinglePlayer = new Boton(400,400,200,40, new ManejadorCambiaEstado(ESTADO_SINGLE));
	btnSinglePlayer->setearMensaje("Juego en Solitario");
}

void EstadoMenuPrincipal::crearVistas(){
	vistaBtnMulti = new VistaBoton("src/gui/resources/botonPrincipalMulti.bmp","src/gui/resources/botonPrincipalMultiClic.bmp");
	vistaBtnSingle = new VistaBoton("src/gui/resources/botonPrincipalSingle.bmp","src/gui/resources/botonPrincipalSingleClic.bmp");
	btnMultiPlayer->agregarObservador(vistaBtnMulti);
	btnSinglePlayer->agregarObservador(vistaBtnSingle);
	fondo = new Superficie("src/gui/resources/fondoPrincipal.jpg");
	fondo->escala(800,600);

	/*TODO:
	 animacion = superMegaAnimacionDeFondo(); jaja
	 */
}

void EstadoMenuPrincipal::terminar(){
	if (fondo){
		delete (fondo);
		fondo = NULL;
	}
	if (btnMultiPlayer){
		delete (btnMultiPlayer);
		btnMultiPlayer = NULL;
	}
	if (btnSinglePlayer){
		delete (btnSinglePlayer);
		btnSinglePlayer = NULL;
	}
	if (vistaBtnMulti){
		delete (vistaBtnMulti);
		vistaBtnMulti = NULL;
	}
	if (vistaBtnSingle){
		delete (vistaBtnSingle);
		vistaBtnSingle = NULL;
	}
	if (animacion){
		delete (animacion);
		animacion = NULL;
	}
}

void EstadoMenuPrincipal::manejarEvento(SDL_Event* evento){
	btnSinglePlayer->manejarEvento(evento);
	if (ManejadorEstados::obtenerEstadoActual() == obtenerInstancia())
		btnMultiPlayer->manejarEvento(evento);
}

void EstadoMenuPrincipal::actualizar(float delta){
	btnSinglePlayer->actualizar();
	btnMultiPlayer->actualizar();
}

void EstadoMenuPrincipal::dibujar(SDL_Surface* display){
	fondo->dibujar(display,0,0);
	vistaBtnSingle->dibujar(display);
	vistaBtnMulti->dibujar(display);
	/*animacion->dibujar(display, 400,200);
	animacion->animar();*/
}
