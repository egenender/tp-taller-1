/*
 * Actualizable.cpp
 *
 *  Created on: 12/10/2012
 *      Author: martin
 */

#include "Actualizable.h"

Actualizable::Actualizable() {
	// TODO Auto-generated constructor stub

}

Actualizable::~Actualizable() {
	// TODO Auto-generated destructor stub
}

void Actualizable::chocarConManual(Manual*){}
void Actualizable::chocarConPlataforma(Plataforma*){}
void Actualizable::chocarConEscalera(Escalera*){}
void Actualizable::chocarConBarril(Barril*){}
void Actualizable::chocarConHongo(Hongo*){}

bool Actualizable::estaMuerto(){
	return false;
}
