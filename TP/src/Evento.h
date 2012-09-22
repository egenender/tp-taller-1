#ifndef EVENTO_H
#define EVENTO_H

#include "SDL/SDL.h"

class Evento {
public:
	Evento();

	virtual ~Evento();

	virtual void manejarEvento(SDL_Event* Event);

	// Se pueden agregar mas eventos, para teclado, mouse, ventana, etc

	virtual void salir();
};

#endif
