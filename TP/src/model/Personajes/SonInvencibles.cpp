/*
 * SonInvencibles.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: genender
 */

#include "SonInvencibles.h"

SonInvencibles::SonInvencibles() {
	// TODO Auto-generated constructor stub
	invencible = false;
	dummies = new std::vector<Dummy*>();
}

SonInvencibles::~SonInvencibles() {
	// TODO Auto-generated destructor stub
}

void SonInvencibles::agregarDummy(Dummy* dummy){
	dummies->push_back(dummy);
}

bool SonInvencibles::mataAlContacto(){
	bool esta = false;
	unsigned int i = 0;
	while( !esta && i < dummies->size() ){
		esta = (dummies->at(i)->mataAlContacto() );
		i++;
	}
	invencible = esta;
	return invencible;
}



int SonInvencibles::obtenerEstado(){
	return 0;
}

int SonInvencibles::obtenerAncho(){
	return 0;
}

int SonInvencibles::obtenerAlto(){
	return 0;
}

Posicion* SonInvencibles::obtenerPosicion(){
	return NULL;
}
