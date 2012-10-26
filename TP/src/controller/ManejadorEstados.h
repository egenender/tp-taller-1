#ifndef MANEJADORESTADOS_H
#define MANEJADORESTADOS_H

#include "Estado.h"

// Lista de estados validos:
enum {
	ESTADO_NINGUNO = 0,
	ESTADO_INTRO,
	ESTADO_JUEGO,
	ESTADO_GUI,
	ESTADO_MENU
};

class ManejadorEstados {
	private:
		static Estado* estadoActivo;

	public:
		static void manejarEvento(SDL_Event* evento);
		static void actualizar(float delta);
		static void dibujar(SDL_Surface* display);
		static void setearEstadoActual(int ID);
		static Estado* obtenerEstadoActual();
};

#endif
