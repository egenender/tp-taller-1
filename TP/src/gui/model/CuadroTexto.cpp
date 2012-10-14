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
	//estado = INACTIVO;
}

CuadroTexto::CuadroTexto(int x, int y, int ancho, int alto,
		unsigned int cantCaracteres) :
		ObjetoGUI::ObjetoGUI(x, y, ancho, alto) {
		maximosCaracteres = cantCaracteres;
		estado = INACTIVO;
		permitido = true;
		validar = TODO;
}


CuadroTexto::CuadroTexto(int x, int y, int ancho, int alto,
		unsigned int cantCaracteres, int posibles) :
		ObjetoGUI::ObjetoGUI(x, y, ancho, alto) {
		maximosCaracteres = cantCaracteres;
		estado = INACTIVO;
		permitido = true;
		validar = posibles;
}

CuadroTexto::~CuadroTexto() {

}

void CuadroTexto::manejarEvento(SDL_Event* evento) {
	int x, y;
	Uint8 estadoMouse = SDL_GetMouseState(&x, &y);
	bool estaEncima = mouseEncima(x,y);
	if ((SDL_MOUSEBUTTONDOWN & SDL_BUTTON(estadoMouse)) == SDL_BUTTON_LEFT) {
		if (estaEncima){
			if (estado != ACTIVO){
				estado = ACTIVO;
				huboCambios();
			}
		}else{
			if (estado != INACTIVO){
				estado = INACTIVO;
				permitido = true;
				huboCambios();
			}
		}
	}

	if (obtenerEstado() == INACTIVO)
		return;
	if (!visible) return;

	string temp = mensajeEscrito;

	if (evento->type == SDL_KEYUP){
		permitido = true;
	}

	if (evento->type == SDL_KEYDOWN) {
		if (mensajeEscrito.length() < maximosCaracteres && caracterValido(evento) && permitido) {
			mensajeEscrito += (char) evento->key.keysym.unicode;
		}

		if ((evento->key.keysym.sym == SDLK_BACKSPACE)
				&& (mensajeEscrito.length() != 0)) {
			mensajeEscrito.erase(mensajeEscrito.length() - 1);
		}
		permitido = false;
	}

	 if(mensajeEscrito != temp) {
		 huboCambios();
	 }
}

bool CuadroTexto::caracterValido(SDL_Event* evento){
	bool esNumerico =(evento->key.keysym.unicode >= (Uint16) '0')
							&& (evento->key.keysym.unicode <= (Uint16) '9');
	bool esEspacio = (evento->key.keysym.unicode == (Uint16) ' ');
	bool esMayuscula = (evento->key.keysym.unicode >= (Uint16) 'A')
							&& (evento->key.keysym.unicode <= (Uint16) 'Z');
	bool esMinuscula = (evento->key.keysym.unicode >= (Uint16) 'a')
							&& (evento->key.keysym.unicode <= (Uint16) 'z');
	bool esPunto = (evento->key.keysym.unicode == (Uint16) '.');

	if (validar == NUMEROS)
		return esNumerico;

	if (validar == LETRAS)
		return (esMayuscula || esMinuscula || esEspacio || esPunto);

	if (validar == NUMEROSYPUNTO)
		return (esNumerico || esPunto);

	return (esNumerico || esEspacio || esMayuscula || esMinuscula || esPunto);

}

string CuadroTexto::obtenerMensaje() {
	return mensajeEscrito;
}
