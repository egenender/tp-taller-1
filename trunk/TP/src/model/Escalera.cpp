/*
 * Escalera.cpp
 *
 *  Created on: 29/10/2012
 *      Author: martin
 */

#include "Escalera.h"

Escalera::Escalera(const char* nom, Area* sup):Cuerpo(nom,sup) {

}

Escalera::~Escalera() {

}

int Escalera::obtenerEstado(){
	return 0;
}

void Escalera::actualizar(float delta){

}


void Escalera::chocarCon(Actualizable* ac){
	ac->chocarConEscalera(this);
}
void Escalera::chocarConManual(Manual*){}
void Escalera::chocarConPlataforma(Plataforma*){}
void Escalera::chocarConEscalera(Escalera*){}
