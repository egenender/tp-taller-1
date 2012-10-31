/*
 * ImagenGUI.cpp
 *
 *  Created on: 15/10/2012
 *      Author: martin
 */

#include "ImagenGUI.h"

ImagenGUI::ImagenGUI(string ruta, string texto, int x, int y, int ancho, int alto) : ObjetoGUI (x,y,ancho,alto){
	sup = new Superficie(ruta);
	sup->transparencia(255,0,255);
	label = new Label(x,y,ancho,alto-25);
	label->setearMensaje(texto);
	vista = new VistaLabel();
	label->agregarObservador(vista);
}

ImagenGUI::~ImagenGUI() {
	if (sup) {
		delete (sup);
		sup = NULL;
	}
	if (vista) {
		delete (vista);
		vista = NULL;
	}
	if (label) {
		delete (label);
		label = NULL;
	}
}

bool ImagenGUI::dibujar(SDL_Surface *display){
	if (!visible) return true;
	label->actualizar();
	sup->dibujar(display, obtenerX(), obtenerY());
	vista->dibujar(display);
	return true;
}

