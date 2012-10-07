#include "VistaBoton.h"
#include "../../gui/model/Boton.h"

VistaBoton::VistaBoton(string rutaInactivo, string rutaActivo) {
	x = y = 0;
	activo = new Superficie(rutaActivo);
	inactivo = new Superficie(rutaInactivo);
	actual = inactivo;
}

VistaBoton::~VistaBoton() {
	if (activo) {
		delete(activo);
		activo = NULL;
	}
	if (inactivo) {
		delete(inactivo);
		inactivo = NULL;
	}

	actual = NULL;
}

void VistaBoton::actualizar(Observable* observable) {
	Boton* boton = (Boton*) observable;

	x = boton->obtenerX();
	y = boton->obtenerY();

	if (boton->esClickeado())
		actual = activo;
	else
		actual = inactivo;
}

bool VistaBoton::dibujar(SDL_Surface* display) {
	return actual->dibujar(display, x, y);
}
