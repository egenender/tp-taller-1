#ifndef VISTAPROTAGONISTA_H_
#define VISTAPROTAGONISTA_H_

#include "VistaAnimada.h"
#include "../model/Observable.h"
//#include "../gui/model/BarraEstado.h"

class VistaProtagonista : public VistaAnimada {
	//Barra* barra;
	//bool primeraVez;
	bool invisible;
public:
	VistaProtagonista(/*Observable* protagonista, */Animacion*, Animacion*, Animacion*);
	~VistaProtagonista();
	void actualizar(Observable* observable);
	void reiniciar();
	bool dibujar(SDL_Surface* display, int xCamara, int yCamara, bool debug);
};

#endif /* VISTAPROTAGONISTA_H_ */
