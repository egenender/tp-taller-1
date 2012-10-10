#include "Boton.h"
#include <exception>

Boton::Boton(int x, int y, int ancho, int alto, ManejadorBoton* m) : ObjetoGUI::ObjetoGUI(x,y,ancho,alto){
	clickeado = false;
	estaEncima = false;
	manejador = m;
}

Boton::~Boton() {
	try{
		delete(manejador);
	}catch(exception& e){
		//Ya lo eliminaron, no hago nada
	}
}

void Boton::manejarEvento(SDL_Event* evento) {
	if (obtenerEstado() == INACTIVO )return;
	int x, y;
	Uint8 estadoMouse = SDL_GetMouseState(&x, &y);
	estaEncima = mouseEncima(x,y);

	if ((SDL_MOUSEBUTTONDOWN & SDL_BUTTON(estadoMouse)) == SDL_BUTTON_LEFT) {
		if (estaEncima) {
			manejador->manejarClic();
			clickeado = true;
		}
	}

	else
		clickeado = false;

	huboCambios();
}

bool Boton::mouseEncima(int x, int y) {
	return ((x > dimensiones.x) && (x < dimensiones.x + dimensiones.w)
			&& (y > dimensiones.y) && (y < dimensiones.y + dimensiones.h));
}

bool Boton::mouseEncima() {
	return estaEncima;
}

bool Boton::esClickeado() {
	return clickeado;
}
