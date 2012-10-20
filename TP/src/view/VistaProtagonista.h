#ifndef VISTAPROTAGONISTA_H_
#define VISTAPROTAGONISTA_H_

#include "VistaAnimada.h"
#include "../model/Observable.h"
//#include "../gui/model/BarraEstado.h"

class VistaProtagonista : public VistaAnimada {
	//Barra* barra;
	//bool primeraVez;
public:
	VistaProtagonista(/*Observable* protagonista, */Animacion*, Animacion*, Animacion*);
	~VistaProtagonista();
	void actualizar(Observable* observable);

};

#endif /* VISTAPROTAGONISTA_H_ */
