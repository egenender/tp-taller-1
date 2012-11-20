/*
 * Dummy.cpp
 *
 *  Created on: 11/10/2012
 *      Author: martin
 */

#include "Dummy.h"
#include "Tipos.h"

Dummy::Dummy(unsigned int elID, Posicion* posicion, int x, int y){
	ID = elID;
	pos = posicion;
	estado = MUERTO;
	ancho = x;
	alto = y;
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
	pos = new Posicion(x, y);
}

void Dummy::setEstado(int state, int tipo){
	if (tipo == INVENCIBLE){
		invencible = true;
	}else{
		invencible = false;
		matador = false;
	}
	if (tipo == MATADOR){
		matador = true;
		invencible = true;
	}else{
		matador = false;
	}

	estado = state;
}

bool Dummy::esMio(unsigned int comparacion){
	return (comparacion == ID);
}

bool Dummy::estaInvencible(){
	return invencible;
}

bool Dummy::mataAlContacto(){
	return matador;
}

int Dummy::obtenerEstado(){
	return estado;
}

unsigned int Dummy::obtenerID(){
	return ID;
}

Posicion* Dummy::obtenerPosicion(){
	return pos;
}

void Dummy::notificar(){
	huboCambios();
	notificarObservadores();
}

int Dummy::obtenerAncho(){
	return ancho;
}
int Dummy::obtenerAlto(){
	return alto;
}
