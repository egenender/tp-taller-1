#include "ManejadorEstados.h"

// Incluir mas estados aca:
#include "EstadoIntroduccion.h"

Estado* ManejadorEstados::estadoActivo = 0;

/** Se encarga de decirle al estado actual que maneje los eventos **/
void ManejadorEstados::manejarEvento(SDL_Event* evento) {
	if (estadoActivo)
		estadoActivo->manejarEvento(evento);
}

/** Se encarga de decirle al estado actual que se actualice **/
void ManejadorEstados::actualizar() {
	if (estadoActivo)
		estadoActivo->actualizar();
}

/** Se encarga de decirle al estado actual que se dibuje **/
void ManejadorEstados::dibujar(SDL_Surface* display) {
	if (estadoActivo)
		estadoActivo->dibujar(display);
}

/** Setea a un estado como actual, terminando el anterior. **/
void ManejadorEstados::setearEstadoActual(int ID) {

	// Terminamos el estado anterior:
	if (estadoActivo)
		estadoActivo->terminar();

	// Iniciamos el estado correspondiente:
	switch(ID) {
		case ESTADO_NINGUNO:
			estadoActivo = 0;
			break;
		case ESTADO_INTRO:
			estadoActivo = EstadoIntroduccion::obtenerInstancia();
			break;

		// Agregar estados aca
	}

	// Iniciamos el nuevo estado:
	if (estadoActivo)
		estadoActivo->iniciar();
}

/** Devuelve el estado actual **/
Estado* ManejadorEstados::obtenerEstadoActual() {
	return estadoActivo;
}
