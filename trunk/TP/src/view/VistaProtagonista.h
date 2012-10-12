#ifndef VISTAPROTAGONISTA_H_
#define VISTAPROTAGONISTA_H_

#include "VistaAnimada.h"
#include "../model/Observable.h"

class VistaProtagonista : public VistaAnimada {
public:
	VistaProtagonista(Observable* protagonista, Animacion*, Animacion*);
	~VistaProtagonista();
	void actualizar(Observable* observable);

};

#endif /* VISTAPROTAGONISTA_H_ */
