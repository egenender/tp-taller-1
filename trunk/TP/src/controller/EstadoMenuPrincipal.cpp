#include "EstadoMenuPrincipal.h"
#include "../gui/model/ManejadorEjemplo.h"
#include "ManejadorEstados.h"
#include "../gui/model/ManejadorCambiaEstado.h"
#include "../gui/model/Ventana.h"

EstadoMenuPrincipal EstadoMenuPrincipal::instancia;

EstadoMenuPrincipal::EstadoMenuPrincipal() {
	fondo = titulo = NULL;
	btnMultiPlayer = btnSinglePlayer = NULL;
	animacion = NULL;
	vistaBtnMulti = vistaBtnSingle = NULL;
	musica = NULL;
}

EstadoMenuPrincipal::~EstadoMenuPrincipal() {
}

EstadoMenuPrincipal* EstadoMenuPrincipal::obtenerInstancia() {
	return &instancia;
}

void EstadoMenuPrincipal::iniciar(){
	musica = Mix_LoadMUS("./src/resources/estados/musica/Theme Song.ogg");
	crearBtns();
	crearVistas();
}

void EstadoMenuPrincipal::crearBtns(){
	btnMultiPlayer = new Boton(310,400,200,40, new ManejadorCambiaEstado(ESTADO_GUI));
	btnMultiPlayer->setearMensaje("Multijugador en red");
	btnSinglePlayer = new Boton(700,400,200,40, new ManejadorCambiaEstado(ESTADO_SINGLE));
	btnSinglePlayer->setearMensaje("Juego en Solitario");
}

void EstadoMenuPrincipal::crearVistas(){
	vistaBtnMulti = new VistaBoton("src/gui/resources/botonPrincipalMulti.png","src/gui/resources/botonPrincipalMultiClic.png");
	vistaBtnSingle = new VistaBoton("src/gui/resources/botonPrincipalSingle.png","src/gui/resources/botonPrincipalSingleClic.png");
	btnMultiPlayer->agregarObservador(vistaBtnMulti);
	btnSinglePlayer->agregarObservador(vistaBtnSingle);
	fondo = new Superficie("src/gui/resources/fondoPrincipal.jpg");
	fondo->escala(ANCHO_ESTANDARD,ALTO_ESTANDARD);
	titulo = new Superficie("src/gui/resources/titulo.png");

	/*TODO:
	 animacion = superMegaAnimacionDeFondo(); jaja
	 */
}

void EstadoMenuPrincipal::terminar(){
	if (fondo){
		delete (fondo);
		fondo = NULL;
	}
	if(titulo){
		delete(titulo);
		titulo = NULL;
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
	if (musica) {
		Mix_HaltMusic();
		Mix_FreeMusic(musica);
		musica = NULL;
	}
}

void EstadoMenuPrincipal::manejarEvento(SDL_Event* evento){
	if (ManejadorEstados::obtenerEstadoActual() == obtenerInstancia())
		btnSinglePlayer->manejarEvento(evento);
	if (ManejadorEstados::obtenerEstadoActual() == obtenerInstancia())
		btnMultiPlayer->manejarEvento(evento);
}

void EstadoMenuPrincipal::actualizar(float delta){
	btnSinglePlayer->actualizar();
	btnMultiPlayer->actualizar();
}

void EstadoMenuPrincipal::dibujar(SDL_Surface* display){
	if (musica && (Mix_PlayingMusic() == 0)) {
		if (Mix_PlayMusic(musica, -1) == -1) {
			printf("No se puede reproducir la musica\n");
			printf("%s\n", Mix_GetError());
		}
	}

	fondo->dibujar(display,0,0);
	//titulo->dibujar(display, 445,200);
	titulo->dibujar(display, (ANCHO_ESTANDARD - 321)/2, 200);
	vistaBtnSingle->dibujar(display);
	vistaBtnMulti->dibujar(display);
	/*animacion->dibujar(display, 400,200);
	animacion->animar();*/
}
