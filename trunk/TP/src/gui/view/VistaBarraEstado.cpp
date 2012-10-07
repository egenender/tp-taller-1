#include "VistaBarraEstado.h"
#include "../../gui/model/BarraEstado.h"
#include "../../common/Fuente.h"

VistaBarraEstado::VistaBarraEstado() {
	x = y = 0;
	mensajeAnterior = mensajeActual = "";
	mensajeAMostrar = NULL;
}

VistaBarraEstado::~VistaBarraEstado() {
}

void VistaBarraEstado::actualizar(Observable* observable) {
	BarraEstado* barra = (BarraEstado*) observable;

	x = barra->obtenerX();
	y = barra->obtenerY();

	mensajeActual = barra->obtenerMensaje();

	if (mensajeActual.compare(mensajeAnterior) != 0) {
		mensajeAnterior = mensajeActual;
		mensajeAMostrar = TTF_RenderText_Solid(Fuente::obtenerInstancia()->obtenerFuente(), mensajeActual.c_str(), Fuente::obtenerInstancia()->obtenerColor());
	}
}

bool VistaBarraEstado::dibujar(SDL_Surface* display) {

	SDL_Rect rectDest;

	rectDest.x = x;
	rectDest.y = y;

	SDL_BlitSurface(mensajeAMostrar, NULL, display, &rectDest);

	return true;
}
