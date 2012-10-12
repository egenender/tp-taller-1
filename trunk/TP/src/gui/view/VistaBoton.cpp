#include "VistaBoton.h"
#include "../../common/Fuente.h"
#include "../../gui/model/Boton.h"

VistaBoton::VistaBoton(string rutaInactivo, string rutaActivo) {
	x = y = 0;
	activo = new Superficie(rutaActivo);
	inactivo = new Superficie(rutaInactivo);
	actual = inactivo;
	botonHabilitado = true;
	mensajeAnterior = mensajeActual = "";
	mensajeAMostrar = NULL;
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
	visible = boton->esVisible();
	botonHabilitado = (boton->obtenerEstado() == ACTIVO);

	if (boton->esClickeado())
		actual = activo;
	else
		actual = inactivo;

	mensajeActual = boton->obtenerMensaje();
	if (mensajeActual.compare(mensajeAnterior) != 0) {
		mensajeAnterior = mensajeActual;
		SDL_FreeSurface(mensajeAMostrar);
		mensajeAMostrar = TTF_RenderText_Solid(Fuente::obtenerInstancia()->obtenerFuente(), mensajeActual.c_str(), Fuente::obtenerInstancia()->obtenerColor());
	}
}

bool VistaBoton::dibujar(SDL_Surface* display) {

	if (!visible) return true;

	// Dibujo el boton:
	bool dibujeBoton = actual->dibujar(display, x, y);

	/* Centro el texto en el boton */
	SDL_Rect destino;
	int desplazamientoX = (actual->obtenerAncho() - mensajeAMostrar->w) / 2;
	int desplazamientoY = (actual->obtenerAlto() - mensajeAMostrar->h) / 2;

	destino.x = x+desplazamientoX;
	destino.y = y+desplazamientoY;

	// Dibujo el texto:
	SDL_BlitSurface(mensajeAMostrar, NULL, display, &destino);

	return dibujeBoton;
}
