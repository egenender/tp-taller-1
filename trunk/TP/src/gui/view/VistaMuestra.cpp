/*
 * VistaMuestra.cpp
 *
 *  Created on: 15/10/2012
 *      Author: martin
 */

#include "VistaMuestra.h"

VistaMuestra::VistaMuestra() {
	visible = false;
	vistaActual = NULL;
	tonto = new Dummy(0);
}

VistaMuestra::~VistaMuestra() {
	if (tonto){
		delete (tonto);
		tonto = NULL;
	}
}

void VistaMuestra::actualizar(Observable* observable){
	Muestra* muestra = (Muestra*) observable;
	visible = muestra->esVisible();

	tonto->setXY(muestra->obtenerX(), muestra->obtenerY());
	tonto->setEstado(QUIETODER);
	vistaActual = muestra->obtenerActual();
	if (vistaActual)
		vistaActual->actualizar(tonto);
}

bool VistaMuestra::dibujar(SDL_Surface* display){
	if (!visible) return true;

	if (!vistaActual) return false;

	return vistaActual->dibujar(display,0,0);
}
