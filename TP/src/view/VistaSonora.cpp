#include "VistaSonora.h"
#include "../log/Log.h"
#include <exception>
using namespace std;

VistaSonora::VistaSonora() {
	estadoActual = estadoAnterior = -1;
	sonidoActual = NULL;
	sonidoAnterior = NULL;
	sonidos = new map<int, Mix_Chunk*>();
	pararDeReproducir = false;
	debeReproducir = false;
	caminando = false;
}

Mix_Chunk* VistaSonora::cargarSonido(string ruta) {
	return Mix_LoadWAV(ruta.c_str());
}

bool VistaSonora::agregarSonido(string ruta, int estado) {
	if (!sonidos)
		return false;

	Mix_Chunk* sonido = cargarSonido("./" + ruta);
	if (!sonido) {
		printf("No se pudo cargar la ruta: %s\n", ruta.c_str());
		printf("%s\n", Mix_GetError());
		return false;
	}

	sonidos->insert(pair<int, Mix_Chunk*>(estado, sonido));

	return true;
}

VistaSonora::~VistaSonora() {
	if (sonidos != NULL) {
		map<int, Mix_Chunk*>::iterator iter;
		for (iter = sonidos->begin(); iter != sonidos->end(); ++iter) {
			Mix_Chunk* sound = (*iter).second;
			if (sound != NULL) {
				Mix_FreeChunk(sound);
				sound = NULL;
			}
		}
		sonidos->clear();
		delete (sonidos);
		sonidos = NULL;
	}

	debeReproducir = false;
	pararDeReproducir = true;
}

void VistaSonora::actualizar(Observable* observable) {
	estadoAnterior = estadoActual;

	estadoActual = observable->obtenerEstado();
	if (estadoActual == MUERTO) {
		pararDeReproducir = true;
		debeReproducir = false;
		return;
	}

	caminando = false;

	// TODO: esto deberia mejorarse:
	if (estadoActual == SALTANDODER || estadoActual == SALTANDOIZQ)
		estadoActual = SALTAR;
	else if (estadoActual == CAMINANDOIZQ || estadoActual == CAMINANDODER) {
		estadoActual = CAMINANDODER;
		caminando = true;
	}

	sonidoAnterior = sonidoActual;
	try {
		sonidoActual = sonidos->at(estadoActual);
	}
	catch (exception &e) {
		// Esto si no encuentro el sonido:
		sonidoActual = NULL;
	}

	if (estadoAnterior == estadoActual && !caminando) {
		debeReproducir = false;
		pararDeReproducir = false;
		return;
	}

	pararDeReproducir = false;
	debeReproducir = true;
}

bool VistaSonora::dibujar(SDL_Surface* display, int x, int y) {
	return reproducir();
}

bool VistaSonora::reproducir() {
	if (sonidoActual == NULL) {
		return false;
	}

	if (debeReproducir && !pararDeReproducir) {
		// El sonido se ejecuta una sola vez:

		if (Mix_Playing(0) && estadoActual == estadoAnterior)
			return true;

		if (Mix_PlayChannel(0, sonidoActual, 0) == -1) {
			Log::getInstance()->writeToLogFile(Log::ERROR,
					"Error al intentar reproducir sonido actual");
			return false;
		}
	}

	return false;
}
