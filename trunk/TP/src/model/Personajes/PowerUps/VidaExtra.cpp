
#include "VidaExtra.h"

VidaExtra::VidaExtra(const char* nom, Area* sup, int vel): PowerUp(nom, sup, vel) {

}

VidaExtra::~VidaExtra() {

}

void VidaExtra::chocarConManual(Manual* prin){
	prin->aumentarVida();
	estado = MUERTO;
	huboCambios();
	notificarObservadores();
}
