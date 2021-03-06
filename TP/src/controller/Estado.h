#ifndef ESTADO_H
#define ESTADO_H

#include "Evento.h"
#include "../view/FPS.h"

class Estado: public Evento {
	public:
		Estado();

	public:
		virtual void manejarEvento(SDL_Event* evento) = 0;
		virtual void iniciar() = 0;
		virtual void terminar() = 0;
		virtual void actualizar(float delta) = 0;
		virtual void dibujar(SDL_Surface* display) = 0;
};

#endif
