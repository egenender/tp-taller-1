#ifndef MANEJADORESTADOS_H
#define MANEJADORESTADOS_H

#include "Estado.h"

// Lista de estados validos:

#define	ESTADO_NINGUNO 0
#define	ESTADO_INTRO 1
#define	ESTADO_MENU 2
#define	ESTADO_GUI 3
#define	ESTADO_SINGLE 4
#define	ESTADO_JUEGO 5

class ManejadorEstados {
	private:
		static Estado* estadoActivo;
		static int siguienteEstado;
		static bool cambiaEstado;

	public:
		static void manejarEvento(SDL_Event* evento);
		static void actualizar(float delta);
		static void dibujar(SDL_Surface* display);
		static void setearEstadoActual(int ID);
		static Estado* obtenerEstadoActual();
		static void cambiarEstado();
};

#endif
