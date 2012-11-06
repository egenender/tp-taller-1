
#include "Cuerpo.h"

Cuerpo::Cuerpo(const char* nombrecito,Area* sup) {
	superficieOcupada = sup;
	nombre = nombrecito;
	superficieDeColision = NULL;
	posAnterior = NULL;
}

Cuerpo::~Cuerpo() {
	delete (superficieOcupada);
	if(superficieDeColision){
		delete(superficieDeColision);
	}
	if(posAnterior) delete(posAnterior);

	//delete (nombre);
	//Podría pasarse una función que destruya a los observadores...
}

Posicion* Cuerpo::obtenerPosicion() {
	return superficieOcupada->obtenerPosicion();
}

void Cuerpo::moverA(Posicion* pos){
	superficieOcupada->cambiarPosicion(pos);
	if (superficieDeColision){
		int difAncho = superficieOcupada->obtenerAncho()-superficieDeColision->obtenerAncho();
		int difAlto = superficieOcupada->obtenerAlto()-superficieDeColision->obtenerAlto();
		Posicion* posC = new Posicion(superficieOcupada->obtenerPosicion()->obtenerX() + difAncho/2, superficieOcupada->obtenerPosicion()->obtenerY() + difAlto);
		superficieDeColision->cambiarPosicion(posC);
	}

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

void Cuerpo::trasladar(int factorX, int factorY, bool cambio){
	if (cambio){
		if (posAnterior) delete(posAnterior);
		posAnterior = new Posicion(obtenerArea()->obtenerPosicion()->obtenerX(),obtenerArea()->obtenerPosicion()->obtenerY());
	}
	Posicion* posDesplazamiento = new Posicion (factorX,factorY);
	superficieDeColision->mover(posDesplazamiento);

	superficieOcupada->mover(posDesplazamiento);


	delete(posDesplazamiento);
	huboCambios();

}

Posicion* Cuerpo::obtenerPosicionAnterior(){
	return posAnterior;
}
