/*
 * Checkbox.cpp
 *
 *  Created on: 07/11/2012
 *      Author: nicolas
 */

#include "Checkbox.h"

void Checkbox::inicializar() {
	checked = false;
	estaEncima = false;
	manejador = NULL;
	pressed = false;
}

Checkbox::Checkbox(int x, int y, int ancho, int alto,ManejadorBoton* m) : ObjetoGUI::ObjetoGUI(x,y,ancho,alto) {
	inicializar();
	manejador = m;
}

Checkbox::~Checkbox() {
	if (manejador) {
		delete(manejador);
		manejador = NULL;
	}
}

void Checkbox::setearCheckeado() {
	checked = true;
}

bool Checkbox::mouseEstaEncima() {
	return estaEncima;
}

void Checkbox::manejarEvento(SDL_Event* evento) {
	if (obtenerEstado() == INACTIVO)
		return;
	if (!visible) return;

	if (evento->type == SDL_MOUSEMOTION) {
		estaEncima = mouseEncima(evento->motion.x, evento->motion.y);
	}

	if (evento->type == SDL_MOUSEBUTTONDOWN && estaEncima) {
		if (evento->button.button == SDL_BUTTON_LEFT) {
			pressed = true;
		}
	}

	if (evento->type == SDL_MOUSEBUTTONUP) {
		if (evento->button.button == SDL_BUTTON_LEFT && pressed) {
			pressed = false;
			if (checked)
				checked = false;
			else
				checked = true;
			if (manejador)
				manejador->manejarClic();
		}
	}

	huboCambios();
}

bool Checkbox::esCheckeado() {
	return checked;
}
