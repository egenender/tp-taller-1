#include "Stone.h"
#include "../Manual.h"
#include "../../Tipos.h"

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

unsigned int Stone::obtenerTipo(){
	return TIPO_PU_PIEDRA;
}
