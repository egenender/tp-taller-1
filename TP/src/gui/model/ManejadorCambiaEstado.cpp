#include "ManejadorCambiaEstado.h"
#include "../../controller/ManejadorEstados.h"

ManejadorCambiaEstado::ManejadorCambiaEstado(int state) {
	estadoCambio = state;
}

ManejadorCambiaEstado::~ManejadorCambiaEstado() {
	}

void ManejadorCambiaEstado::manejarClic(){
	ManejadorEstados::setearEstadoActual(estadoCambio);
}
