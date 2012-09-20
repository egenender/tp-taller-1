#ifndef VISTAPROTAGONISTA_H_
#define VISTAPROTAGONISTA_H_

#include "VistaAnimada.h"
#include "Manual.h"

class VistaProtagonista : public VistaAnimada {
public:
	VistaProtagonista(Manual* protagonista);
	~VistaProtagonista();
	void actualizar(Observable* observable);

};

#endif /* VISTAPROTAGONISTA_H_ */
