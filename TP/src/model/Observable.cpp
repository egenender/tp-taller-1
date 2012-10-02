#include "Observable.h"
#include <stdlib.h>

Observable::Observable() {
	cambios = false;
	observadores = new vector<Observador*>();
}

Observable::~Observable() {
	if (observadores != NULL)
		delete(observadores);
}

void Observable::agregarObservador(Observador* observador) {
	if (observador != NULL) {
		// Verifico que ya no este agregado...
		for (unsigned int i = 0; i < observadores->size(); i++) {
			if (observadores->at(i) == observador)
				return;
		}

		observadores->push_back(observador);

		// Esto lo pongo porque sino, hasta que no haya un cambio en el cuerpo, no se actualiza :P
		// Originalmente en el patron (al menos el de Java) esto aca no se hace:
		observador->actualizar(this);
	}
}

void Observable::eliminarObservador(Observador* observador) {
	// Lo busco y lo elimino:
	for (unsigned int i = 0; i < observadores->size(); i++) {
		if (observadores->at(i) == observador) {
			observadores->erase(observadores->begin() + i);
			return;
		}
	}
}

void Observable::limpiarCambio() {
	cambios = false;
}

void Observable::notificarObservadores() {
	//Si no hubo cambios, no hago nada
	if (!cambios) return;

	// Se podría agregar argumentos para decirle a los observadores que fue lo que cambio:
	for (unsigned int i = 0; i < observadores->size(); i++) {
		observadores->at(i)->actualizar(this);
	}
	limpiarCambio();
}

void Observable::huboCambios(){
	cambios = true;
}

bool Observable::cambio() {
	return cambios;
}

int Observable::cantidadObservadores() {
	return observadores->size();
}
