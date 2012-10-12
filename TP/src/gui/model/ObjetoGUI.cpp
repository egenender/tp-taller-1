#include "ObjetoGUI.h"

ObjetoGUI::ObjetoGUI(int x, int y, int ancho, int alto) {
	estado = ACTIVO;
	visible = true;
	dimensiones.x = x;
	dimensiones.y = y;

	if (ancho > 0)
		dimensiones.w = ancho;
	if (alto > 0)
		dimensiones.h = alto;
}

ObjetoGUI::~ObjetoGUI() {}

void ObjetoGUI::actualizar() {
	notificarObservadores();
}

int ObjetoGUI::obtenerX() {
	return dimensiones.x;
}

int ObjetoGUI::obtenerY() {
	return dimensiones.y;
}

int ObjetoGUI::obtenerAncho() {
	return dimensiones.w;
}

int ObjetoGUI::obtenerAlto() {
	return dimensiones.h;
}

int ObjetoGUI::obtenerEstado() {
	return estado;
}

void ObjetoGUI::setearEstado(int estado) {
	this->estado = estado;
}

void ObjetoGUI::manejarEvento(SDL_Event* evento) {
	return;
}

void ObjetoGUI::invisibilizar(){
	if (visible){
		visible = false;
		huboCambios();
	}
}

void ObjetoGUI::visibilizar(){
	if (!visible){
		visible = true;
		huboCambios();
	}
}

Posicion* ObjetoGUI::obtenerPosicion(){
	return (new Posicion(dimensiones.x,dimensiones.y));
}
bool ObjetoGUI::esVisible(){
	return visible;
}
