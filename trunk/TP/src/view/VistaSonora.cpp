#include "VistaSonora.h"
#include "../log/Log.h"
#include <exception>
using namespace std;

VistaSonora::VistaSonora() {
	sonidoActual = NULL;
	sonidoAnterior = NULL;
	sonidos = new map<int, Mix_Chunk*>();
	pararDeReproducir = false;
	debeReproducir = false;
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
	int estado = observable->obtenerEstado();
	if (estado == MUERTO) {
		pararDeReproducir = true;
		debeReproducir = false;
		return;
	}

	// TODO: esto deberia mejorarse:
	else if (estado == SALTANDODER || estado == SALTANDOIZQ)
		estado = SALTAR;
	else if (estado == CAMINANDOIZQ)
		estado = CAMINANDODER;


	pararDeReproducir = false;
	debeReproducir = true;

	sonidoAnterior = sonidoActual;
	try {
		sonidoActual = sonidos->at(estado);
	}
	catch (exception &e) {
		// Esto si no encuentro el sonido:
		sonidoActual = NULL;
	}
}

bool VistaSonora::dibujar(SDL_Surface* display, int x, int y) {
	return reproducir();
}

bool VistaSonora::reproducir() {
	if (sonidoActual == NULL) {
		return false;
	}

	if (sonidoActual != sonidoAnterior && debeReproducir && !pararDeReproducir) {
		// El sonido se ejecuta una sola vez:
		if (Mix_PlayChannel(-1, sonidoActual, 0) == -1) {
			Log::getInstance()->writeToLogFile(Log::ERROR,
					"Error al intentar reproducir sonido actual");
			return false;
		}
		debeReproducir = false; // Esto para que no se vuelva a reproducir, a no ser que cambie el estado.
	}

	return false;
}
