/*
 * Fuente.h
 *
 *  Created on: 06/10/2012
 *      Author: nicolas
 */

#ifndef FUENTE_H_
#define FUENTE_H_

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

class Fuente {
private:
	TTF_Font* font;
	SDL_Color color;
	int size;
	static Fuente instancia;
	Fuente();

public:

	static Fuente* obtenerInstancia();

	bool inicializar();
	void terminar();
	TTF_Font* obtenerFuente();
	SDL_Color obtenerColor();
	int obtenerTamanio();
};

#endif /* FUENTE_H_ */
