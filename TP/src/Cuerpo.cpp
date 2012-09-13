
#include "Cuerpo.h"

Cuerpo::Cuerpo(Area* sup) {
	superficieOcupada = sup;
	lista_observadores = lista_crear();
}

Cuerpo::~Cuerpo() {
	delete superficieOcupada;
	lista_destruir(lista_observadores, NULL);
	//Podría pasarse una función que destruya a los observadores...
}

void Cuerpo::moverA(Posicion* pos){
	superficieOcupada->cambiarPosicion(pos);
}

/*
void Cuerpo::agregarObservador(Observador* observer){
	lista_insertar_utlimo(lista_observadores, observer);
}
 * */
