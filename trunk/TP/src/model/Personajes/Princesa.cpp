#include "Princesa.h"
#include "../Observable.h"

Princesa::Princesa(const char* nom, Area* sup, int t): Cuerpo(nom, sup) {
	tiempo_espera = t;
	if (tiempo_espera < 1)
		tiempo_espera = TIEMPO_ESPERA_STD;

	timer = new Timer();
	estado = QUIETO;
	tiempo_actual = tiempo_espera;
	timer->comenzar();

	int anchoP = 2 * superficieOcupada->obtenerAncho();
	int y = superficieOcupada->obtenerPosicion()->obtenerY();
	int x = superficieOcupada->obtenerPosicion()->obtenerX() - (superficieOcupada->obtenerAncho() / 2);

	superficieDeColision = new Area(anchoP, superficieOcupada->obtenerAlto(), new Posicion(x,y));
}

Princesa::~Princesa() {
	delete(timer);
}

int Princesa::obtenerEstado(){
	return estado;
}

void Princesa::chocarCon(Actualizable* ac){
	ac->chocarConPrincesa(this);
}

void Princesa::actualizar(float){

	if (timer->obtenerTiempo() > (tiempo_actual * 1000)){
		cambiar_estado();
	}
	notificarObservadores();
}

void Princesa::cambiar_estado(){
	if (estado == QUIETO){
		estado = GRITANDO;
		tiempo_actual = TIEMPO_GRITO;
	}else{
		estado = QUIETO;
		tiempo_actual = tiempo_espera;
	}
	huboCambios();
	timer->detener();
	timer->comenzar();
}
