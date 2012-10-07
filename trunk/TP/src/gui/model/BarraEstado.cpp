#include "BarraEstado.h"

BarraEstado::BarraEstado(int x, int y, int ancho, int alto) : ObjetoGUI(x, y, ancho, alto) {
	mensaje = "";
}

BarraEstado::~BarraEstado() {}

void BarraEstado::setearMensaje(string mensaje) {
	this->mensaje = mensaje;
	huboCambios();
}

string BarraEstado::obtenerMensaje() {
	return mensaje;
}
