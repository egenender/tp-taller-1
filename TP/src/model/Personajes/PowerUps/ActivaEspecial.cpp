#include "ActivaEspecial.h"
#include "../Manual.h"

ActivaEspecial::ActivaEspecial(const char* nom, Area* sup, int vel): PowerUp(nom, sup, vel) {

}

ActivaEspecial::~ActivaEspecial() {

}

void ActivaEspecial::chocarConManual(Manual* prin){
	prin->habilitarEspecial();
	estado = MUERTO;
	huboCambios();
	notificarObservadores();
}

