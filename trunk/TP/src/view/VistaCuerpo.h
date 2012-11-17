#ifndef VISTACUERPO_H_
#define VISTACUERPO_H_

#include "Superficie.h"
#include "../common/Observador.h"
#include "../model/Posicion.h"

class VistaCuerpo : public Observador {
protected:
	Posicion* posicionDibujar;
	int estadoActual; // NEW

public:
	VistaCuerpo();
	~VistaCuerpo();
	virtual void actualizar(Observable* observable) = 0;
	virtual bool dibujar(SDL_Surface* display, int xCamara, int yCamara) = 0;
};


#endif /* VISTACUERPO_H_ */
