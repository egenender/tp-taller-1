
#include "Cuerpo.h"

Cuerpo::Cuerpo(const char* nombrecito,Area* sup) {
	superficieOcupada = sup;
	lista_observadores = lista_crear();
	nombre = nombrecito;
}

Cuerpo::~Cuerpo() {
	delete superficieOcupada;
	lista_destruir(lista_observadores, NULL);
	delete nombre;
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

const char* Cuerpo::getNombre(){
	return nombre;
}
/*
void Cuerpo::agregarObservador(Observador* observer){
	lista_insertar_utlimo(lista_observadores, observer);
}
 * */
