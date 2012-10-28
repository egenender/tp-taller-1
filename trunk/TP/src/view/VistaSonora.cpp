#include "VistaSonora.h"
#include "../log/Log.h"

VistaSonora::VistaSonora() {
	sonidoActual = NULL;
	sonidos = new map<int,Mix_Chunk*>();
	pararDeReproducir = false;
	debeReproducir = false;
}

Mix_Chunk* VistaSonora::cargarSonido(string ruta) {
	return Mix_LoadWAV(ruta.c_str());
}

bool VistaSonora::agregarSonido(string ruta, int estado) {
	if (!sonidos)
		return false;

	Mix_Chunk* sonido = cargarSonido(ruta);
	if (!sonido)
		return false;

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
		delete(sonidos);
		sonidos = NULL;
	}

	debeReproducir = false;
	pararDeReproducir = true;
}

void VistaSonora::actualizar(Observable* observable) {
	int estado = observable->obtenerEstado();
	if (estado == MUERTO){
		pararDeReproducir = true;
		debeReproducir = false;
		return;
	}
	pararDeReproducir = false;
	debeReproducir = true;

	sonidoActual = sonidos->at(estado);
}

bool VistaSonora::reproducir() {
	if (sonidoActual == NULL) {
		Log::getInstance()->writeToLogFile(Log::ADVERTENCIA, "Sonido Actual es NULL");
		return false;
	}

	if (debeReproducir && !pararDeReproducir) {
		 if(Mix_PlayChannel(-1, sonidoActual, 0) == -1) {
			 Log::getInstance()->writeToLogFile(Log::ERROR, "Error al intentar reproducir sonido actual");
			 return false;
		 }
		 debeReproducir = false;
	}

	return false;
}
