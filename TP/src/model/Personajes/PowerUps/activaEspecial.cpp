#include "activaEspecial.h"
#include "../Manual.h"

activaEspecial::activaEspecial(const char* nom, Area* sup, int vel): PowerUp(nom, sup, vel) {

}

activaEspecial::~activaEspecial() {

}

void activaEspecial::chocarConManual(Manual* prin){
	prin->habilitarEspecial();
	estado = MUERTO;
	huboCambios();
	notificarObservadores();
}

