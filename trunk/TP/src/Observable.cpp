#include "Observable.h"

Observable::Observable() {
}

Observable::~Observable() {
}

void Observable::agregarObservador(Observador* observador) {
	observadores.push_back(observador);
}

void Observable::eliminarObservador(Observador* observador) {
	for (unsigned int i = 0; i < observadores.size(); i++) {
		if (observadores[i] == observador) {
			observadores.erase(observadores.begin() + i);
			return;
		}
	}
}

void Observable::notificarObservadores() {
	// Se podría agregar argumentos para decirle a los observadores que fue lo que cambio:
	for (unsigned int i = 0; i < observadores.size(); i++) {
		observadores[i]->actualizar(this);
	}
}
