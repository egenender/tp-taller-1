#include "ManejadorEstados.h"

// Incluir mas estados aca:
#include "Nivel.h"
#include "EstadoGUI.h"
#include "EstadoMenuPrincipal.h"
#include "EstadoSinglePlayer.h"

Estado* ManejadorEstados::estadoActivo = 0;
int ManejadorEstados::siguienteEstado;
bool ManejadorEstados::cambiaEstado;
/** Se encarga de decirle al estado actual que maneje los eventos **/
void ManejadorEstados::manejarEvento(SDL_Event* evento) {
	if (estadoActivo)
		estadoActivo->manejarEvento(evento);
}

/** Se encarga de decirle al estado actual que se actualice **/
void ManejadorEstados::actualizar(float delta) {
	if (estadoActivo)
		estadoActivo->actualizar(delta);
}

/** Se encarga de decirle al estado actual que se dibuje **/
void ManejadorEstados::dibujar(SDL_Surface* display) {
	if (estadoActivo)
		estadoActivo->dibujar(display);
}

/** Setea a un estado como actual, terminando el anterior. **/
void ManejadorEstados::setearEstadoActual(int ID) {
	siguienteEstado = ID;
	cambiaEstado = true;
}

/** Devuelve el estado actual **/
Estado* ManejadorEstados::obtenerEstadoActual() {
	return estadoActivo;
}

void ManejadorEstados::cambiarEstado(){
	if (!cambiaEstado) return;
	cambiaEstado = false;

	// Terminamos el estado anterior:
	if (estadoActivo)
		estadoActivo->terminar();

	// Iniciamos el estado correspondiente:
	switch(siguienteEstado) {
	case ESTADO_NINGUNO:
		estadoActivo = 0;
		break;
	case ESTADO_JUEGO:
		estadoActivo = Nivel::obtenerInstancia();
		break;
	case ESTADO_GUI:
		estadoActivo = EstadoGUI::obtenerInstancia();
		break;
	case ESTADO_MENU:
		estadoActivo = EstadoMenuPrincipal::obtenerInstancia();
		break;
	case ESTADO_SINGLE:
		estadoActivo = EstadoSinglePlayer::obtenerInstancia();
		break;
	}

	// Iniciamos el nuevo estado:
	if (estadoActivo)
		estadoActivo->iniciar();


}
