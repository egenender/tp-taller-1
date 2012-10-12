/*
 * Dummy.cpp
 *
 *  Created on: 11/10/2012
 *      Author: martin
 */

#include "Dummy.h"

Dummy::Dummy(unsigned int elID) {
	ID = elID;
	pos = NULL;
}

Dummy::Dummy(unsigned int elID, Posicion* posicion){
	ID = elID;
	pos = posicion;
}

Dummy::~Dummy() {
	if (pos){
		delete (pos);
		pos = NULL;
	}
}

void Dummy::setXY(int x, int y){
	if (pos){
		delete (pos);
	}
	pos = new Posicion(x,y);
}

void Dummy::setEstado(int state){
	estado = state;
}

bool Dummy::esMio(unsigned int comparacion){
	return (comparacion == ID);
}

int Dummy::obtenerEstado(){
	return estado;
}

Posicion* Dummy::obtenerPosicion(){
	return pos;
}

void Dummy::notificar(){
	huboCambios();
	notificarObservadores();
}
