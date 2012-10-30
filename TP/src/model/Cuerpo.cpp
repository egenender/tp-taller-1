
#include "Cuerpo.h"

Cuerpo::Cuerpo(const char* nombrecito,Area* sup) {
	superficieOcupada = sup;
	nombre = nombrecito;
	superficieDeColision = NULL;
}

Cuerpo::~Cuerpo() {
	delete (superficieOcupada);
	if(superficieDeColision){
		delete(superficieDeColision);
	}

	//delete (nombre);
	//Podría pasarse una función que destruya a los observadores...
}

Posicion* Cuerpo::obtenerPosicion() {
	return superficieOcupada->obtenerPosicion();
}

void Cuerpo::moverA(Posicion* pos){
	superficieOcupada->cambiarPosicion(pos);
	huboCambios();
}

int Cuerpo::obtenerAncho() {
	return superficieOcupada->obtenerAncho();
}

int Cuerpo::obtenerAlto() {
	return superficieOcupada->obtenerAlto();
}

const char* Cuerpo::obtenerNombre(){
	return nombre;
}

Area* Cuerpo::obtenerArea(){
	if (superficieDeColision)
		return superficieDeColision;
	return superficieOcupada;
}
