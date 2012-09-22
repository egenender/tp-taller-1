#ifndef VISTAAUTOMATICO_H_
#define VISTAAUTOMATICO_H_
#include "VistaAnimada.h"
#include "Automatico.h"
#define PRIMERA 1
#define SEGUNDA 2

class VistaAutomatico:public VistaAnimada {
private:
	int actual;
	bool terminoAhora;
	int periodo;
public:
	VistaAutomatico(Automatico*, Animacion*, Animacion*, int);
	virtual ~VistaAutomatico();
	void actualizar(Observable* observable);
private:
	void cambiarAnimacion();
};

#endif /* VISTAAUTOMATICO_H_ */
