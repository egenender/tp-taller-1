#include "Stone.h"
#include "../Manual.h"

Stone::Stone(const char* nom, Area* sup, int vel): PowerUp(nom, sup, vel) {

}

Stone::~Stone() {

}

void Stone::chocarConManual(Manual* prin){
	if(prin->obtenerEstado() == HERIDO)
			return ;
	prin->evolucionar();
	estado = MUERTO;
	huboCambios();
	notificarObservadores();
}