#ifndef VISTAPROTAGONISTA_H_
#define VISTAPROTAGONISTA_H_

#include "VistaAnimada.h"
#include "Manual.h"

class VistaProtagonista : public VistaAnimada {
public:
	VistaProtagonista(Manual* protagonista, Animacion*, Animacion*);
	~VistaProtagonista();
	void actualizar(Observable* observable);
	VistaProtagonista(Manual* protagonista);
};

#endif /* VISTAPROTAGONISTA_H_ */
