#include "Caja.h"

Caja::Caja(const char* nom, Area* sup, FabricaActualizable *f): Plataforma(nom, sup) {
	fabrica = f;
	estado = QUIETO;
	timer = new Timer();
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
		timer->comenzar();
	}
	delete(posCmp);
}

void Caja::fabricar(){
	if (!fabrica) return;

	Posicion* pos = new Posicion(obtenerArea()->obtenerPosicion()->obtenerX() + obtenerArea()->obtenerAncho()/2, obtenerArea()->obtenerPosicion()->obtenerY()-1);

	fabrica->fabricar(pos, ARRIBA_FABR);
	delete(pos);

}

void Caja::actualizar(float){
	if (estado == QUIETO) return;

	if (timer->obtenerTiempo() >= (TIEMPO_CAJA*1000)){
		timer->detener();
		estado = QUIETO;
		huboCambios();
		notificarObservadores();
	}
}
