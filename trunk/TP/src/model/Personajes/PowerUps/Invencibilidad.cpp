#include "Invencibilidad.h"
#include "../Manual.h"
#include "../../Tipos.h"

Invencibilidad::Invencibilidad(const char* nom, Area* sup, int vel):PowerUp(nom, sup, vel) {
	timer = new Timer();
	timer->comenzar();
	puedoMovermeEnElAire = true;
}

Invencibilidad::~Invencibilidad() {
	delete(timer);
}

void Invencibilidad::chocarConManual(Manual* prin){
	if(prin->obtenerEstado() == HERIDO)
		return;
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


void Invencibilidad::saltar(){
	if(!tengoPiso) return;
	velocidadY = -20;
	tengoPiso = false;
}

void Invencibilidad::validarPiso(){
	if (obtenerArea()->estaSobreElPiso() || tengoPiso){
		tengoPiso = true;
		saltar();
		huboCambios();
	}
}

unsigned int Invencibilidad::obtenerTipo(){
	return TIPO_PU_INVENCIBILIDAD;
}
