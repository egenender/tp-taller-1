#include "ActivaEspecial.h"
#include "../Manual.h"

ActivaEspecial::ActivaEspecial(const char* nom, Area* sup, int vel): PowerUp(nom, sup, vel) {
	timer = new Timer();
	timer->comenzar();
}

ActivaEspecial::~ActivaEspecial() {
	delete(timer);
}

void ActivaEspecial::chocarConManual(Manual* prin){
	prin->habilitarEspecial();
	estado = MUERTO;
	huboCambios();
	notificarObservadores();
}

void ActivaEspecial::actualizarMovimiento(){
	//Nada de movimiento, simplemente me fijo si me muero o no
	if (timer->obtenerTiempo() >= (TIEMPO_VIDA_ESPECIAL *1000)){
		estado = MUERTO;
		huboCambios();
		notificarObservadores();
		timer->detener();
	}

}
