/*
 * VistaCheckbox.cpp
 *
 *  Created on: 07/11/2012
 *      Author: nicolas
 */

#include "VistaCheckbox.h"
#include "../model/Checkbox.h"

VistaCheckbox::VistaCheckbox(string fondo, string tilde) {
	x = y = 0;
	box = new Superficie(fondo);
	if (box)
		box->transparencia(255,0,255);
	this->tilde = new Superficie(tilde);
	if (this->tilde)
		this->tilde->transparencia(255,0,255);
	actual = box;
	habilitado = true;
	ancho = alto = 0;
	visible = false;
}

VistaCheckbox::~VistaCheckbox() {
	if (box) {
		delete(box);
		box = NULL;
	}
	if (tilde) {
		delete(tilde);
		tilde = NULL;
	}
}

void VistaCheckbox::actualizar(Observable* observable) {
	Checkbox* checkbox = (Checkbox*) observable;

	x = checkbox->obtenerX();
	y = checkbox->obtenerY();
	visible = checkbox->esVisible();
	habilitado = (checkbox->obtenerEstado() == ACTIVO);

	if (checkbox->esCheckeado())
		actual = tilde;
	else
		actual = box;

	ancho = checkbox->obtenerAncho();
	alto = checkbox->obtenerAlto();
	if (tilde)
		tilde->escala(ancho,alto);
	if (box)
		box->escala(ancho,alto);
}

bool VistaCheckbox::dibujar(SDL_Surface* display) {
	if (!display || !actual)
		return false;

	if (!visible) return true;

	return actual->dibujar(display, x, y);

}


