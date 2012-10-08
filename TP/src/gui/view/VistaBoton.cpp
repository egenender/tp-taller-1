#include "VistaBoton.h"
#include "../../gui/model/Boton.h"

VistaBoton::VistaBoton(string rutaInactivo, string rutaActivo) {
	x = y = 0;
	activo = new Superficie(rutaActivo);
	inactivo = new Superficie(rutaInactivo);
	actual = inactivo;
	botonHabilitado = true;
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

	botonHabilitado = (boton->obtenerEstado() == ACTIVO);

	if (boton->esClickeado())
		actual = activo;
	else
		actual = inactivo;
}

bool VistaBoton::dibujar(SDL_Surface* display) {
	/*Si no esta habilitado el boton, dibujo*/
	if (!botonHabilitado) return true;
	return actual->dibujar(display, x, y);
}
