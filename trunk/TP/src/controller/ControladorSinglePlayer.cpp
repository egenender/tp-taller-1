#include "ControladorSinglePlayer.h"
#include "GestorConfiguraciones.h"
#include "ManejadorEstados.h"

ControladorSinglePlayer::ControladorSinglePlayer(Manual* ob) {
	principal = ob;
}

ControladorSinglePlayer::~ControladorSinglePlayer() {

}


// VIEJO MANEJAR EVENTO:
void ControladorSinglePlayer::manejarEvento(SDL_Event* evento) {

// NEW:
	if (!principal)
		return;
	// end NEW

	Uint8 *keystates = SDL_GetKeyState(NULL);

	if (keystates[SDLK_ESCAPE]) {
		GestorConfiguraciones::getInstance()->acabarGestor();
		ManejadorEstados::setearEstadoActual(ESTADO_MENU);
		return;
	}

//New
	// Si el controlado no acepta movimiento, no hay nada que hacer:
	if (!principal->puedeMover())
		return;
// end NEW


	//Lo dejo por separado, por si hay que cambiarle algo :P
	if(principal->estaMuerto()){
		//GestorConfiguraciones::getInstance()->acabarGestor();
		GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
		gestor->quienGano = gestor->ObtenerPosiblesTiposProtagonistas()->size();
		ManejadorEstados::setearEstadoActual(ESTADO_TERMINADO);
		return;
	}

	if (principal->esGanador()){
		//GestorConfiguraciones::getInstance()->acabarGestor();
		GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
		gestor->quienGano = principal->obtenerID();
		ManejadorEstados::setearEstadoActual(ESTADO_TERMINADO);
		return;
	}

	if (keystates[SDLK_z]){
		principal->especial();
	}

	if (keystates[SDLK_UP] && !keystates[SDLK_DOWN]){
		principal->subir();
	}
	if (keystates[SDLK_DOWN] && !keystates[SDLK_UP]){
		principal->bajar();
	}

	if (keystates[SDLK_SPACE]) {
		principal->saltar();
	}

	if (keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT]) {
		principal->moverALaIzquierda();
	}

	if (keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT]) {
		principal->moverALaDerecha();
	}

	//TODO: en este if va a haber que agregar mas condiciones cuando se permita saltar/etc..
	if (!(keystates[SDLK_LEFT] ^ keystates[SDLK_RIGHT]) && !(keystates[SDLK_UP] ^ keystates[SDLK_DOWN])) {
		principal->detener();
	}
}
