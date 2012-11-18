/*
 * VistaSonora.h
 *
 *  Created on: 27/10/2012
 *      Author: nicolas
 */

#ifndef VISTASONORA_H_
#define VISTASONORA_H_

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "../model/Observable.h"
#include "VistaCuerpo.h"
#include <string>
#include <map>
using namespace std;

class VistaSonora : public VistaCuerpo {
protected:
	int estadoActual, estadoAnterior;
	map<int,Mix_Chunk*>* sonidos;
	Mix_Chunk* sonidoActual, *sonidoAnterior;
	bool pararDeReproducir, debeReproducir, caminando;
private:
	Mix_Chunk* cargarSonido(string ruta);

public:
	VistaSonora();
	~VistaSonora();

	bool agregarSonido(string ruta, int estado);
	void actualizar(Observable* observable);
	bool dibujar(SDL_Surface* display, int x, int y); // solo llama al reproducir
	bool reproducir(); // aka: dibujar();
};

#endif /* VISTASONORA_H_ */
