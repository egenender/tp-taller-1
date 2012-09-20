#ifndef VISTACUERPO_H_
#define VISTACUERPO_H_

#include "SDL/SDL.h"
#include "Observador.h"
#include "Posicion.h"

class VistaCuerpo : public Observador {
protected:
	Posicion* posicionDibujar;

public:
	VistaCuerpo();
	~VistaCuerpo();
	virtual void actualizar(Observable* observable) = 0;
	virtual bool dibujar(SDL_Surface* display) = 0;
};


#endif /* VISTACUERPO_H_ */
