#ifndef VISTACUERPO_H_
#define VISTACUERPO_H_

#include "Superficie.h"
#include "../common/Observador.h"
#include "../model/Posicion.h"

class VistaCuerpo : public Observador {
protected:
	Posicion* posicionDibujar, *posicionColision;
	Superficie* supDebug;

public:
	VistaCuerpo();
	~VistaCuerpo();
	virtual void actualizar(Observable* observable);
	virtual bool dibujar(SDL_Surface* display, int xCamara, int yCamara, bool debug) = 0;
};


#endif /* VISTACUERPO_H_ */
