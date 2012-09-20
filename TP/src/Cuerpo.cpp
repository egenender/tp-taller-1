
#include "Cuerpo.h"

Cuerpo::Cuerpo(const char* nombrecito,Area* sup) {
	superficieOcupada = sup;
	nombre = nombrecito;
}

Cuerpo::~Cuerpo() {
	delete (superficieOcupada);
	delete (nombre);
	//Podría pasarse una función que destruya a los observadores...
}

Posicion* Cuerpo::obtenerPosicion() {
	return superficieOcupada->getPosicion();
}

void Cuerpo::moverA(Posicion* pos){
	superficieOcupada->cambiarPosicion(pos);
}

int Cuerpo::obtenerAncho() {
	return superficieOcupada->getAncho();
}

int Cuerpo::obtenerAlto() {
	return superficieOcupada->getAlto();
}

const char* Cuerpo::obtenerNombre(){
	return nombre;
}
