#include "Caja.h"

Caja::Caja(const char* nom, Area* sup, FabricaActualizable *f): Plataforma(nom, sup) {
	fabrica = f;
	estado = QUIETO;
}

Caja::~Caja() {
	if (fabrica)
		delete(fabrica);
}

void Caja::chocarConManual(Manual* pers){
	if (estado != QUIETO) return;

	Posicion* posPers = pers->obtenerPosicionAnterior();

	Posicion* posCmp = new Posicion (obtenerArea()->obtenerPosicion()->obtenerX(), obtenerArea()->obtenerPosicion()->obtenerY()+obtenerArea()->obtenerAlto());

	if (posPers->estaAbajoDe(posCmp)){
		estado = LANZANDO;
		fabricar();
		huboCambios();
		notificarObservadores();
	}
	delete(posCmp);
}

void Caja::fabricar(){
	if (!fabrica) return;

	fabrica->fabricar(obtenerArea()->obtenerPosicion(), 0);

}
