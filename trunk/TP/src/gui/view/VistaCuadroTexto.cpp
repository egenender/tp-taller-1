/*
 * VistaCuadroTexto.cpp
 *
 *  Created on: 12/10/2012
 *      Author: nicolas
 */

#include "VistaCuadroTexto.h"
#include "../../gui/model/CuadroTexto.h"
#include "../../common/Fuente.h"

void VistaCuadroTexto::inicializar() {
	x = y = ancho = alto = 0;
	mensajeActual = "";
	mensajeAMostrar = NULL;
	cuadroSinFoco = NULL;
}

VistaCuadroTexto::VistaCuadroTexto() {
	inicializar();
	cuadroSinFoco = new Superficie("src/gui/resources/cuadradoBlanco.jpg");
	cuadroConFoco = new Superficie("src/gui/resources/cuadradoBlancoFoco.bmp");
	imagenActual = cuadroSinFoco;
}

VistaCuadroTexto::~VistaCuadroTexto() {
	if (cuadroSinFoco) {
		delete(cuadroSinFoco);
		cuadroSinFoco = NULL;
	}
	if (mensajeAMostrar) {
		delete(mensajeAMostrar);
		mensajeAMostrar = NULL;
	}
	if (cuadroConFoco){
		delete(cuadroConFoco);
		cuadroConFoco = NULL;
	}
}

void VistaCuadroTexto::actualizar(Observable* observable) {
	CuadroTexto* cuadro = (CuadroTexto*) observable;

	x = cuadro->obtenerX();
	y = cuadro->obtenerY();
	alto = cuadro->obtenerAlto();
	ancho = cuadro->obtenerAncho();
	visible = cuadro->esVisible();

	if (mensajeActual.compare(cuadro->obtenerMensaje()) != 0) {
		mensajeActual = cuadro->obtenerMensaje();
		if (mensajeAMostrar)
			SDL_FreeSurface(mensajeAMostrar);
		mensajeAMostrar = TTF_RenderText_Solid(Fuente::obtenerInstancia()->obtenerFuente(), mensajeActual.c_str(), Fuente::obtenerInstancia()->obtenerColor());
	}

	// Por si hay que redimencionarla:
	cuadroSinFoco->escala(ancho, alto);
	cuadroConFoco->escala(ancho,alto);

	if (cuadro->obtenerEstado() == ACTIVO)
		imagenActual = cuadroConFoco;
	else
		imagenActual = cuadroSinFoco;
}

bool VistaCuadroTexto::dibujar(SDL_Surface* display) {
	if (!visible) return true;
	// Dibujo la barra:
	bool dibujeCuadro = imagenActual->dibujar(display, x, y);

	if (mensajeAMostrar == NULL)
		return false;

	/* Centro el texto en la barra */
	SDL_Rect destino;
	int desplazamientoY = (alto - mensajeAMostrar->h) / 2;
	int desplazamientoX = (ancho - mensajeAMostrar->w) / 2;
	destino.x = x+desplazamientoX;
	destino.y = y+desplazamientoY;

	// Dibujo el texto:
	SDL_BlitSurface(mensajeAMostrar, NULL, display, &destino);

	return dibujeCuadro;
}
