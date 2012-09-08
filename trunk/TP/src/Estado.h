#ifndef ESTADO_H
#define ESTADO_H

#include "Evento.h"

class Estado: public Evento {
	public:
		Estado();

	public:
		virtual void iniciar() = 0;
		virtual void terminar() = 0;
		virtual void actualizar() = 0;
		virtual void dibujar(SDL_Surface* display) = 0;
};

#endif
