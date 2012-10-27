#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_
#include "Evento.h"
#include "../model/Observable.h"

class Controlador {
public:
	Controlador();
	virtual ~Controlador();
	virtual void manejarEvento(SDL_Event*)=0;
};

#endif /* CONTROLADOR_H_ */
