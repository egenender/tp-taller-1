#include "ObjetoGUI.h"

ObjetoGUI::ObjetoGUI(int x, int y, int ancho, int alto) {
	estado = ACTIVO;

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

int ObjetoGUI::obtenerEstado() {
	return estado;
}

void ObjetoGUI::setearEstado(int estado) {
	this->estado = estado;
}

void ObjetoGUI::manejarEvento(SDL_Event* evento) {
	return;
}

void ObjetoGUI::activar(){
	if (estado != INACTIVO){
		estado = INACTIVO;
		huboCambios();
	}
}

void ObjetoGUI::desactivar(){
	if (estado != ACTIVO){
		estado = ACTIVO;
		huboCambios();
	}
}
