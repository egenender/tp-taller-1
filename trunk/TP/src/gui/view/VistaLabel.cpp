#include "VistaLabel.h"
#include "../../common/Fuente.h"
void VistaLabel::inicializar() {
	x = y = ancho = alto = 0;
	mensajeAnterior = mensajeActual = "";
	mensajeAMostrar = NULL;
	visible = true;
}

VistaLabel::VistaLabel() {
	inicializar();
}

VistaLabel::~VistaLabel() {
	if (mensajeAMostrar){
		delete(mensajeAMostrar);
		mensajeAMostrar = NULL;
	}
}

void VistaLabel::actualizar(Observable* observable) {
	Label* label = (Label*) observable;

	visible = label->esVisible();

	x = label->obtenerX();
	y = label->obtenerY();
	alto = label->obtenerAlto();
	ancho = label->obtenerAncho();

	mensajeActual = label->obtenerMensaje();

	if (mensajeActual.compare(mensajeAnterior) != 0) {
		mensajeAnterior = mensajeActual;
		SDL_FreeSurface(mensajeAMostrar);
		mensajeAMostrar = TTF_RenderText_Solid(Fuente::obtenerInstancia()->obtenerFuente(), mensajeActual.c_str(), Fuente::obtenerInstancia()->obtenerColor());
	}

}

bool VistaLabel::dibujar(SDL_Surface* display) {
	if (!display)
		return false;
	if (!visible) return true;
	// Dibujo la barra:

	if(!mensajeAMostrar)
		return false;

	/* Centro el texto en la barra */
	SDL_Rect destino;
	int desplazamientoY = (alto - mensajeAMostrar->h) / 2;
	int desplazamientoX = (ancho - mensajeAMostrar->w) / 2;
	destino.x = x+desplazamientoX;
	destino.y = y+desplazamientoY;

	// Dibujo el texto:
	SDL_BlitSurface(mensajeAMostrar, NULL, display, &destino);

	return true;
}


