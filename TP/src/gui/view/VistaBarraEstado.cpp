#include "VistaBarraEstado.h"
#include "../../gui/model/BarraEstado.h"
#include "../../common/Fuente.h"

void VistaBarraEstado::inicializar() {
	x = y = ancho = alto = 0;
	mensajeAnterior = mensajeActual = "";
	mensajeAMostrar = NULL;
	barraEstado = NULL;
	visible = true;
	notificacion = NULL;
	hayNotificacion = false;
}

VistaBarraEstado::VistaBarraEstado() {
	inicializar();
	barraEstado = new Superficie("src/gui/resources/barraEstado.bmp");
	notificacion = Mix_LoadWAV("./src/gui/resources/notification.ogg");
/*	if(barraEstado)
		SDL_BlitSurface(mensajeAMostrar, NULL, barraEstado->obtenerSurface(), NULL);*/
}

VistaBarraEstado::~VistaBarraEstado() {
	if (barraEstado) {
		delete(barraEstado);
		barraEstado = NULL;
	}
	if (mensajeAMostrar) {
		delete(mensajeAMostrar);
		mensajeAMostrar = NULL;
	}

	if (notificacion) {
		Mix_FreeChunk(notificacion);
		notificacion = NULL;
	}
}

void VistaBarraEstado::actualizar(Observable* observable) {
	BarraEstado* barra = (BarraEstado*) observable;

	visible = barra->esVisible();

	x = barra->obtenerX();
	y = barra->obtenerY();
	alto = barra->obtenerAlto();
	ancho = barra->obtenerAncho();

	mensajeActual = barra->obtenerMensaje();

	if (mensajeActual.compare(mensajeAnterior) != 0) {
		mensajeAnterior = mensajeActual;
		SDL_FreeSurface(mensajeAMostrar);
		mensajeAMostrar = TTF_RenderText_Solid(Fuente::obtenerInstancia()->obtenerFuente(), mensajeActual.c_str(), Fuente::obtenerInstancia()->obtenerColor());
		hayNotificacion = true;
	}

	// Por si hay que redimencionarla:
	barraEstado->escala(ancho, alto);
}

bool VistaBarraEstado::dibujar(SDL_Surface* display) {
	if (!display)
		return false;

	if (!visible) return true;

	if (notificacion && hayNotificacion)
		Mix_PlayChannel(-1, notificacion, 0);

	hayNotificacion = false;

	// Dibujo la barra:
	bool dibujeBarra = barraEstado->dibujar(display, x, y);

	if (!mensajeAMostrar)
		return false;

	/* Centro el texto en la barra */
	SDL_Rect destino;
	int desplazamientoY = (alto - mensajeAMostrar->h) / 2;
	int desplazamientoX = (ancho - mensajeAMostrar->w) / 2;
	destino.x = x+desplazamientoX;
	destino.y = y+desplazamientoY;

	// Dibujo el texto:
	SDL_BlitSurface(mensajeAMostrar, NULL, display, &destino);

	return dibujeBarra;
}

bool VistaBarraEstado::dibujar(SDL_Surface* display, int x, int y) {
	return dibujar(display);
}
