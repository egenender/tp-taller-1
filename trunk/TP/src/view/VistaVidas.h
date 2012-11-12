#ifndef VISTAVIDAS_H_
#define VISTAVIDAS_H_
#include "VistaCuerpo.h"
#include "../model/Observable.h"
#include "Superficie.h"
#define DIM_CORAZON 60

class VistaVidas :public VistaCuerpo{
private:
	Superficie* sup, *timeout;
	int vidas;
	bool tieneTimeout;

public:
	VistaVidas();
	virtual ~VistaVidas();
	void actualizar(Observable* observable);
	bool dibujar(SDL_Surface* display, int xCamara, int yCamara);
};

#endif /* VISTAVIDAS_H_ */
