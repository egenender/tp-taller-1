/*
 * CuadroTexto.cpp
 *
 *  Created on: 12/10/2012
 *      Author: nicolas
 */

#include "CuadroTexto.h"

void CuadroTexto::inicializar() {
	mensajeEscrito = "";
	maximosCaracteres = 0;
}

CuadroTexto::CuadroTexto(int x, int y, int ancho, int alto,
		unsigned int cantCaracteres) :
		ObjetoGUI::ObjetoGUI(x, y, ancho, alto) {
	maximosCaracteres = cantCaracteres;
}

CuadroTexto::~CuadroTexto() {
}

void CuadroTexto::manejarEvento(SDL_Event* evento) {
	int x, y;
	Uint8 estadoMouse = SDL_GetMouseState(&x, &y);
	bool estaEncima = mouseEncima(x,y);
	if ((SDL_MOUSEBUTTONDOWN & SDL_BUTTON(estadoMouse)) == SDL_BUTTON_LEFT) {
		if (estaEncima) {
			setearEstado(ACTIVO);
		}
	}

	if (obtenerEstado() == INACTIVO)
		return;

	string temp = mensajeEscrito;

	if (evento->type == SDL_KEYDOWN) {
		if (mensajeEscrito.length() < maximosCaracteres) {
			if (evento->key.keysym.unicode == (Uint16) ' ') {
				mensajeEscrito += (char) evento->key.keysym.unicode;
			}
			else if ((evento->key.keysym.unicode >= (Uint16) '0')
					&& (evento->key.keysym.unicode <= (Uint16) '9')) {
				mensajeEscrito += (char) evento->key.keysym.unicode;
			} else if ((evento->key.keysym.unicode >= (Uint16) 'A')
					&& (evento->key.keysym.unicode <= (Uint16) 'Z')) {
				mensajeEscrito += (char) evento->key.keysym.unicode;
			} else if ((evento->key.keysym.unicode >= (Uint16) 'a')
					&& (evento->key.keysym.unicode <= (Uint16) 'z')) {
				mensajeEscrito += (char) evento->key.keysym.unicode;
			}
		}

		if ((evento->key.keysym.sym == SDLK_BACKSPACE)
				&& (mensajeEscrito.length() != 0)) {
			mensajeEscrito.erase(mensajeEscrito.length() - 1);
		}
	}

	 if(mensajeEscrito != temp) {
		 huboCambios();
	 }
}

string CuadroTexto::obtenerMensaje() {
	return mensajeEscrito;
}


bool CuadroTexto::mouseEncima(int x, int y) {
	return ((x > dimensiones.x) && (x < dimensiones.x + dimensiones.w)
			&& (y > dimensiones.y) && (y < dimensiones.y + dimensiones.h));
}