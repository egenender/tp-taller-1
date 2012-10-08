#include "Boton.h"

Boton::Boton(int x, int y, int ancho, int alto) : ObjetoGUI::ObjetoGUI(x,y,ancho,alto){
	clickeado = false;
	estaEncima = false;
}

Boton::~Boton() {}

void Boton::manejarEvento(SDL_Event* evento) {
	if (obtenerEstado() == INACTIVO )return;
	int x, y;
	Uint8 estadoMouse = SDL_GetMouseState(&x, &y);
	estaEncima = mouseEncima(x,y);

	if ((SDL_MOUSEBUTTONDOWN & SDL_BUTTON(estadoMouse)) == SDL_BUTTON_LEFT) {
		if (estaEncima) {
			printf("Click\n");
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
