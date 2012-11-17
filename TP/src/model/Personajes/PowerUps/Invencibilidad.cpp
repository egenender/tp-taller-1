#include "Invencibilidad.h"
#include "../Manual.h"

Invencibilidad::Invencibilidad(const char* nom, Area* sup, int vel):PowerUp(nom, sup, vel) {
	timer = new Timer();
	timer->comenzar();
}

Invencibilidad::~Invencibilidad() {
	delete(timer);
}

void Invencibilidad::chocarConManual(Manual* prin){
	if(prin->obtenerEstado() == HERIDO)
			return ;
	prin->hacerInvencible();
	estado = MUERTO;
	huboCambios();
	notificarObservadores();
}


void Invencibilidad::actualizarMovimiento(){
	PowerUp::actualizarMovimiento();
	//Nada de movimiento, simplemente me fijo si me muero o no
	if (timer->obtenerTiempo() >= (TIEMPO_VIDA_INVENCIBILIDAD *1000)){
		estado = MUERTO;
		huboCambios();
		notificarObservadores();
		timer->detener();
	}

}


